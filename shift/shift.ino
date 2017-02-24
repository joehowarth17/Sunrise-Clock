const int data = 5;
const int rclck = 8;
const int sclck = 10;
char incomingByteA = 0;
//int incomingByteB = 0;
int incomingByte = 0 ;
const int d = 100;
const int s = 115;
const int l = 108;
const int zero = 48;
const int one = 49 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(data, OUTPUT);
  pinMode(sclck, OUTPUT);
  pinMode(rclck, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("main loop. serial not available");
  int count = 0;
  byte command = 0;
  while (count < 8) {
    if (Serial.available() > 0) {
      // read the incoming byte:
      Serial.println("serial.avalable>0");
      incomingByte = Serial.read()-48;
      Serial.println(incomingByte);
      //incomingByteB = Serial.read();
      if(incomingByte == 1){bitSet(command,count);
      }
      else{
        bitClear(command,count);
        }
      Serial.println("line read");
      // Serial.println(incomingByteA);
      //Serial.println(incomingByteB);
      Serial.println(command);
      
      count += 1;
    }
  }
  Serial.println(command, HEX);
  digitalWrite(rclck, LOW);
  shiftOut(data, sclck, MSBFIRST, command);  
  digitalWrite(rclck, HIGH);
  /*if (command == (d + zero)) {
    digitalWrite(data, LOW);
    Serial.println("Data: LOW");
  }
  if (command == (d + one)) {
    digitalWrite(data, HIGH);
    Serial.println("Data: HIGH");
  }

  if (command == (l + zero)) {
    digitalWrite(rclck, LOW);
    Serial.println("register: LOW");
  }
  if (command == (l + one)) {
    digitalWrite(rclck, HIGH);
    Serial.println("register: HIGH");
  }

  if (command == (s + zero)) {
    digitalWrite(sclck, LOW);
    Serial.println("clock: LOW");
  }
  if (command == (s + one)) {
    digitalWrite(sclck, HIGH);
    Serial.println("clock: HIGH");
  }*/
}

