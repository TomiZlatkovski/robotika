#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 7);

const int frontLeftWheel = 8; //desno nazad
const int frontRightWheel = 9; //desno napred
const int backLeftWheel = 10; // levo napred
const int backRightWheel = 11; //levo nazad
const int leftSpeed = 5;
const int rightSpeed = 4;

struct CarControls {

  void ForwardTurn(int speedLeft, int speedRight) {
    analogWrite(leftSpeed, speedLeft);
    analogWrite(rightSpeed, speedRight);
    digitalWrite(backLeftWheel, HIGH);
    digitalWrite(frontRightWheel, HIGH);
  }

  void BackTurn(int speedLeft, int speedRight)
  {
    analogWrite(leftSpeed, speedLeft);
    analogWrite(rightSpeed, speedRight);
    digitalWrite(backRightWheel, HIGH);
    digitalWrite(frontLeftWheel, HIGH);
  }
};

CarControls Kola;
String msg = "";

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
}


void loop() {
  

  if(BTSerial.available() > 0) {
    char val = BTSerial.read();
  }

  BTSerial.write(111);
  // put your main code here, to run repeatedly:
  //digitalWrite(10, HIGH);
  //Kola.ForwardTurn(50, 200);
  //Kola.BackTurn(100, 200);
  //digitalWrite(8, HIGH);
  //digitalWrite(9, HIGH);
  //digitalWrite(backRightWheel, HIGH);
  //digitalWrite(4, HIGH);
  //delay(1000);
}
