#include <NewPing.h>
#include <Servo.h>

Servo myservo;

#define TRIGGER_PIN  7
#define ECHO_PIN     6
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
boolean Checked = false;
boolean LCheck = false;
boolean RCheck = false;
int long AvoidTime;

void setup() {
  Serial.begin(9600);
  myservo.attach(3);
  myservo.write(90);
}

void loop() {
  int dist = sonar.ping_cm();
  Serial.println(dist);
  if (dist <= 20 && Checked == false) {
    obstacle();
  }


}

void obstacle() {
  int long t = micros();
  int long  Ls;
  int long  Rs;
  int  dist = sonar.ping_cm();
  while (dist <= 20 && LCheck == false) {
    Ls = t;
    myservo.write(180);
  }
  int long Lt = t - Ls;
  myservo.write(90);
  myservo.write(0);
  delayMicroseconds(Lt);
  myservo.write(90);
  LCheck=true;
  while (dist <= 20 && RCheck == false) {
    Rs = t;
    myservo.write(0);
  }
  int long Rt = t - Rs;
  myservo.write(90);
  myservo.write(180);
  delayMicroseconds(Rt);
  RCheck=true; 
  if(Rt>=Lt){
    AvoidTime=Rt;
  }
   if(Lt>Rt){
    AvoidTime=Lt;
  }
  
  Checked=false;


}


