#include <SoftwareSerial.h>
#include <string.h>
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

SoftwareSerial BTSerial(4, 7); // rx pa tx

/*
 Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
*/

struct Motor {
  int maxAngle, minAngle, currentAngle;
  String name;

  Motor(String _name, int _maxAngle, int _minAngle, int _currentAngle) {
    name = _name;
    maxAngle = _maxAngle;
    minAngle = _minAngle;
    currentAngle = _currentAngle;
  }

  void setAngle(int angle) {
    currentAngle = angle;
  }

  int getAngle() {
    return currentAngle;
  }

};
Motor Base("Base",180,0,90);
Motor Shoulder("Shoulder",165,15,45);
Motor Elbow("Elbow",180,0,180);
Motor WristV("WristV",180,0,180);
Motor WristR("WristR",180,0,90);
Motor Grip("Grip",73,10,10);

Motor Motors[6] = { Base, Shoulder, Elbow, WristV, WristR, Grip };

void MoveMotor(String motorName, int angle) {
  bool found = false;
  for(int i=0; i<6; i++) {
    if((Motors[i].name == motorName)) {
      Motors[i].setAngle(angle);
      found = true;
      break;
    }
  }

  if(!found) {
    BTSerial.write("Vnesovte nevaliden motor!");
  }
}

void setup() {
  Braccio.begin();
  BTSerial.begin(9600);
  Serial.begin(9600);
}

String msg = "";

void loop() {
  if(BTSerial.available() > 0) {
    char val = BTSerial.read();
    if(val == ';') {
      String firstParam = "";
      int secondParam = 0;
      bool first = true;

      for(int i=0; i<msg.length(); ++i) {
        if(msg[i] == ',') {
          first = false;
          continue;
        }

        if(first) firstParam += msg[i];
        else{
          secondParam = atoi(&msg[i]);
          break;
        }
      }

      if(firstParam[0] == 13 || firstParam[0] == 10) firstParam = firstParam.substring(2);
      MoveMotor(firstParam, secondParam);
      Serial.print(firstParam == "Base");
      Braccio.ServoMovement(30, Motors[0].currentAngle, Motors[1].currentAngle, Motors[2].currentAngle,
          Motors[3].currentAngle, Motors[4].currentAngle, Motors[5].currentAngle);

      msg = "";
    }
    else {
      msg += val;
    }
  }
}
