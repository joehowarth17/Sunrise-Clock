/******************************* For RESP8266 **********************************/
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char ssid[] = "D84E74";
const char password[] = "261675263";

MDNSResponder mdns;

ESP8266WebServer server(80);

/******************************* For RGB LEDs **********************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN       14

#define NUMPIXELS      5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

/******************************************************************************/

#define DEBUG          1

void connectToWifi();

void handleIndex();
void handleNotFound();
void handleSetColor();

void sendColor(uint8_t r, uint8_t g, uint8_t b);

/******************************************************************************/
void setup() {
Serial.begin(115200);
pixels.begin();

connectToWifi();

if(mdns.begin("Light", WiFi.localIP())){

  if(DEBUG){
    Serial.println("mDNS is up and running");
    }
  }
server.on("/", handleIndex);
server.onNotFound(handleNotFound);
server.on("/setColor", handleSetColor);

server.begin();

MDNS.addService("http","tcp",80);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  
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
    for(int j = 0; j<4;j++){
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
    server.send(200, "text/plain", " Welcome to the main page!!");
    delay(100);
  }

void handleNotFound(){

      if(DEBUG){
      Serial.println("handling page not found");
      }
    server.send(200, "text/plain", "That Page Doesm't exist!");
    delay(100);
  }

void handleSetColor(){

  String r = server.arg("red");
  String g = server.arg("green");
  String b = server.arg("blue");
  sendColor(r.toInt(),g.toInt(), b.toInt());
  char data[2];
  data[0] = 0xD0 | (r.toInt()%60);
  data[1] = ((g.toInt()%7)<<5) | (b.toInt()%24);
  Serial.write(data,2);
  server.send(200, "text/plain", "Color Sent");
  }

void sendColor(uint8_t r, uint8_t g, uint8_t b){
  
  for(int i = 0; i<NUMPIXELS;i++){

    pixels.setPixelColor(i,pixels.Color(r,g,b));
    
    }

    pixels.show();
    delay(50);
  }






















  
