#include <Wire.h>
byte* a;
//byte* b;
void setup() {
  // put your setup code here, to run once:
Wire.begin(); 
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Wire.beginTransmission(0x03);
Wire.write(0);
Wire.endTransmission();
Wire.requestFrom(0x03,1);
*a = Wire.read();
//*b = Wire.read();
//byte b = Wire.read();
//Serial.print(*b,BIN);
Serial.println(*a,BIN);

delay(2000);
}
