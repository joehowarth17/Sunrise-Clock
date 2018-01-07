/******************************* For ESP8266 ***********************************/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>




/******************************* WiFI + Server *********************************/

const char ssid[] = "2WIRE444";
const char password[] = "1903625393";

MDNSResponder mdns;                  

ESP8266WebServer server(80);          
/********************************  UDP  NTP ***********************************/

WiFiUDP Udp;

uint8_t maxDnsFails = 3;

IPAddress ntpServerIP;
const char* ntpHostName = "time.windows.com" ; //host name for the ntp server canada

const int NTP_PACKET_SIZE = 48;

byte NTP_BUFFER[NTP_PACKET_SIZE];


/******************************** Interrupts ***********************************/

const byte interruptPinSunrise = 12;

volatile byte flagS = 0;
volatile byte flagT = 0;
const byte interruptPinTime = 13;



/********************************* RGB LEDs ************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN       14

#define NUMPIXELS      5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

const uint8_t SUNRISE_R = 250; // max value of red in sunrise
const uint8_t SUNRISE_G = 200; // max value of green in sunrise
const uint8_t SUNRISE_B = 125; // max value of blue in sunrise

byte sunriseMin = 2; // global variable holding time it takes for sunrise

/******************************************************************************/

#define DEBUG         0

void connectToWifi(); // connects to wifi and indicates connection with led flash and serial print

void handleIndex();
void handleNotFound();
void handleSetColor();
void showAlarm();
void setAlarm();
void showSetColor();

void sendColor(uint8_t r, uint8_t g, uint8_t b); // sets all led to the specified color
void sunrise(uint8_t minutes);                  // increases the brightness of the leds over the time specified

void sunriseInterrupt();                        // isr to start the sunrise when alarm is set off
void timeInterrupt();

void startUdp();                               
void ntpRequest();
uint32_t receiveNtp();
uint32_t getTime();
void sendTime();
/******************************************************************************/
void setup() {
 
Serial.begin(9600);

pixels.begin();
pixels.clear();


connectToWifi();

//start up mdns
if(mdns.begin("Light", WiFi.localIP())){

  if(DEBUG){
    Serial.println("mDNS is up and running");
    }
  }

// set up server handling
server.on("/", handleIndex);
server.onNotFound(handleNotFound);
server.on("/setAlarm",HTTP_GET, showAlarm);
server.on("/setAlarm",HTTP_POST, setAlarm);
server.on("/setColor",HTTP_POST, handleSetColor);
server.on("/setColor",HTTP_GET,showSetColor);

server.begin();
startUdp();

MDNS.addService("http","tcp",80);

//set up interrupts
pinMode(interruptPinSunrise,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPinSunrise),sunriseInterrupt,FALLING);

pinMode(interruptPinTime,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPinTime),timeInterrupt,FALLING);


// flash leds to show that esp8266 is up an running
for(int i = 0; i < NUMPIXELS;i++){
pixels.setPixelColor(i,pixels.Color(0,0,60));}
pixels.show();
delay(500);
for(int i = 0; i < NUMPIXELS;i++){
pixels.setPixelColor(i,pixels.Color(0,0,0));}
pixels.show();


}

void loop() {
  // put your main code here, to run repeatedly:
  
  server.handleClient();
  if(flagS){
    if(DEBUG)Serial.println(flagS, HEX);
    sunrise(sunriseMin);
    }
   if(flagT){
    if(DEBUG)Serial.println(flagT, HEX);
    sendTime(getTime()+2);
    
    }
    
  
}




void connectToWifi(){
  
  WiFi.begin(ssid, password);

  if(DEBUG){
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }

  while(WiFi.status() != WL_CONNECTED){
    
      delay(500);
      if(DEBUG) Serial.print(".");
    }

    // Flash leds twice to show esp is connected
    for(int j = 0; j<2;j++){
    for(int i = 0; i<NUMPIXELS; i++){

        if(j%2 ==0){
          pixels.setPixelColor(i,pixels.Color(0,0,60)); 
        }
        else{
           pixels.setPixelColor(i,pixels.Color(0,0,0));  
          }
        
      }
      pixels.show();
      delay(500);
      }
    

  if(DEBUG){
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    
    }
  
  }


void handleIndex(){
    if(DEBUG){
      Serial.println("handling Index");
      }
    server.send(200, "html","<!DOCTYPE html><html><head><title>ESP8266 Lights</title></head><body><h1>Welcome !!</h1><p><a href=\"setColor\">Change the color of the Leds</a></p><p><a href=\"setAlarm\">Set the alarm</a></p></body></html>");
    //" Welcome to the main page!!"
    delay(100);

  }

void handleNotFound(){

      if(DEBUG){
      Serial.println("handling page not found");
      }
    server.send(404, "text/plain", "That Page Doesn't exist!");
    delay(100);
  }

void showSetColor(){
  if(DEBUG)Serial.println("showing set color");
  server.send(200, "html", "<!DOCTYPE html><html><head><title>ESP8266 Lights</title></head><body><h1>Enter RGB Values</h1><p><form method=\"POST\">  Red:<br>  <input type=\"text\" name=\"red\" ><br>  Green:<br>  <input type=\"text\" name=\"green\" ><br>  Blue:<br>  <input type=\"text\" name=\"blue\" ><br><br>  <input type=\"submit\" value=\"Submit\"></form></p></body></html>");

    }
void handleSetColor(){
  server.sendHeader("Location","/setColor");
  server.send(303);
  String r = server.arg("red");
  String g = server.arg("green");
  String b = server.arg("blue");
  if(DEBUG){
    Serial.println(r);
     Serial.println(g);
      Serial.println(b);
      
  }
  sendColor(r.toInt(),g.toInt(), b.toInt());
  }

void showAlarm(){
  
    if(DEBUG)Serial.println("showing set Alarm");
    server.send(200,"html","<!DOCTYPE html><html><head><title>ESP8266 Lights</title></head><body><p><form method= \"POST\">Hour:<br><input type=\"text\" name=\"hour\"> <br> Minute:<br> <input type = \"text\" name=\"minute\"><br><br>Weekdays:<br><input type=\"checkbox\" name=\"Sunday\">Sunday<input type=\"checkbox\" name=\"Monday\">Monday<input type=\"checkbox\" name=\"Tuesday\">Tuesday<input type=\"checkbox\" name=\"Wednesday\">Wednesday<input type=\"checkbox\" name=\"Thursday\">Thursday<input type=\"checkbox\" name=\"Friday\">Friday<input type=\"checkbox\" name=\"Saturday\">Saturday<br><input type=\"submit\" value=\"Submit\"></form></p></body></html>");
  
  }
void setAlarm(){
  if(DEBUG)Serial.println("alarm received");
  server.sendHeader("Location","/");
  server.send(303);
  byte hours   = server.arg("hour").toInt();
  byte minutes = server.arg("minute").toInt();
  byte wkdays = 0;

// each bit of wkday corresponds to a day, sunday throught saturday from right to left
  if(server.hasArg("Sunday")){

      wkdays += 1;
    }
  if(server.hasArg("Monday")){
      
      wkdays += 2;
    }
  if(server.hasArg("Tuesday")){
    
      wkdays += 4;
    }
  if(server.hasArg("Wednesday")){
    
      wkdays += 8;
    }
  if(server.hasArg("Thursday")){
    
      wkdays += 16;
    }
  if(server.hasArg("Friday")){
    
      wkdays += 32;
    }
  if(server.hasArg("Saturday")){
    
      wkdays += 64;
    }
    
  if(wkdays == 0){
    
    wkdays = 0xFF;
    }
  

  char data[3]; 
  data[0] = (minutes%60); // minute
  data[1] = (hours%24);   // hour
  data[2] = wkdays ;      // weekdays

  if(DEBUG){
    
    Serial.println(data[0],HEX);
    Serial.println(data[1],HEX);
    Serial.println(data[2],HEX);
    }
  Serial.write(data[0]);
  Serial.write(data[1]);
  Serial.write(data[2]);
  
  }

void sendColor(uint8_t r, uint8_t g, uint8_t b){
  
  for(int i = 0; i<NUMPIXELS;i++){

    pixels.setPixelColor(i,pixels.Color(r,g,b));
    
    }

    pixels.show();
    delay(50);
  }


void sunrise(uint8_t minutes){
  
  uint16_t totalS = minutes * 60; // 60 seconds per minute
  uint16_t currentS = 0;

  float constR = ((float)SUNRISE_R / (float)sq(totalS));
  float constG = ((float)SUNRISE_G /(float) sq(totalS));
  float constB = ((float)SUNRISE_B / (float)sq(totalS));
  if(DEBUG)Serial.println(constR);
  if(DEBUG)Serial.println(constG);
  if(DEBUG)Serial.println(constB);

  pixels.clear();

  while(currentS<totalS){


    
    for(int i = 0; i<NUMPIXELS;i++){

    pixels.setPixelColor(i,pixels.Color(constR*sq(currentS),constG*sq(currentS),constB*sq(currentS)));
    
    }

    pixels.show();
    
    // Let ESP8266 handle requests, subtract time from delay to get constant overall delays
    unsigned long t1 = millis();
    server.handleClient();
    unsigned long t2 = millis();
    if(DEBUG)Serial.println(1000-(t2-t1));
    delay(1000 - (t2-t1));
    currentS++ ;
    
    }
    flagS =0;
    if(DEBUG)Serial.println(flagS, HEX);
    if(DEBUG)Serial.print("done sunrise!");
    pixels.clear();
    pixels.show();
  }

void sunriseInterrupt(){
   if(DEBUG)Serial.println("sunrise interrupt");
  flagS = 1;
  }

void timeInterrupt(){
if(DEBUG)Serial.println("time inttrpt");
  flagT = 1; 
}

void startUdp(){
  
  Udp.begin(123); // listen on port 123
  
  uint8_t tries = 0;
  
  while((!WiFi.hostByName(ntpHostName,ntpServerIP))){
    
    if(DEBUG)Serial.println(ntpServerIP);

    }

  if(DEBUG)Serial.println("udp working");
  } 

                            
void ntpRequest(){
  if(DEBUG)Serial.println("requesting ntp");
  memset(NTP_BUFFER,0,NTP_PACKET_SIZE);

  NTP_BUFFER[0] = 0xE3; // 1110 0011

  Udp.beginPacket(ntpServerIP,123);
  Udp.write(NTP_BUFFER,NTP_PACKET_SIZE);
  Udp.endPacket();
  }

uint32_t receiveNtp(){
  //if(DEBUG)Serial.println("recieving ntp response");
  if(Udp.parsePacket() == 0){
    
    return 0;
    }

  Udp.read(NTP_BUFFER,NTP_PACKET_SIZE);
  // combine bytes into full 32 bit number
  uint32_t ntpTime = NTP_BUFFER[40] << 24 | NTP_BUFFER[41] << 16 | NTP_BUFFER[42] << 8 | NTP_BUFFER[43] ; 
  return ntpTime;
  }

uint32_t getTime(){
  if(DEBUG)Serial.println("getting Time");

  unsigned long interval = 30000; // 30 seconds
  unsigned long current = millis();
  
  
  boolean done = false;

  unsigned long requestTime = millis();
  ntpRequest();

  while(!done || interval > 240000){

    current = millis();
    
    if((current-requestTime)>interval){

      if(DEBUG)Serial.println("Sending ntp request");
      ntpRequest();
      interval *= 2;
      requestTime = current;
      
      }

      uint32_t ntpTime = receiveNtp();
      //if(DEBUG)Serial.println(ntpTime);
      if(ntpTime){
        
        done = true;
        if(DEBUG){
          Serial.print("Time Received");
          Serial.print((ntpTime/60)%60);
          Serial.print("min, ");
          Serial.print(ntpTime%60);
          Serial.print("sec.");
          }

          return ntpTime;
        
        }
        else{server.handleClient();
        }
    
    }
  
 
  
  }
  
void sendTime(uint32_t ntpTime){

    uint8_t seconds = ntpTime%60;
    uint8_t minutes = (ntpTime/60)%60;

    byte data[3];
    data[0] = 0xC0|seconds;
    data[1] = minutes;
    data[2] = 0; // psoc expects three bytes

    if(DEBUG){
    
    Serial.println(data[0],HEX);
    Serial.println(data[1],HEX);
    Serial.println(data[2],HEX);
    }

    Serial.write(data[0]);
    Serial.write(data[1]);
    Serial.write(data[2]);

    flagT = 0;
    if(DEBUG)Serial.println(flagT, HEX);
  }


 











  
