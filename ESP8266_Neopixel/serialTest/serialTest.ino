
const char data = 0xFA;//1111 1010
const char data2 = 0xF0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.write(data);
  delay(1500);
  
    Serial.write(data2);
    delay(1500);
  

}
