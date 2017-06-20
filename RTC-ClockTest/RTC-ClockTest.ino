#include <Wire.h>
const int PCF8523_ADDRESS =byte( 0x68);

void setup() {
  // put your setup code here, to run once:
Wire.begin(); 
Serial.begin(9600);
}
int reading =0;
void loop() {
  // put your main code here, to run repeatedly:

Wire.beginTransmission(PCF8523_ADDRESS);
Wire.write(byte(0x00));
Wire.endTransmission();

Wire.requestFrom(PCF8523_ADDRESS,3);
if (3 <= Wire.available()) { // if two bytes were received
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 16;    // shift high byte to be high 8 bits
    reading |= Wire.read()<<8; // receive low byte as lower 8 bits
    reading |= Wire.read();
    Serial.println(reading);   // print the reading
  }

delay(1000);
}
