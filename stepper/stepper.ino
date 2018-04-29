#include <AccelStepper.h>
#include <MultiStepper.h>

#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1
int n;
int x=0;
int y;

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(150.0);
  stepper1.setSpeed(600);
  Serial.begin(9600);


}//--(end setup )---

void loop() {
  if (Serial.available() > 0)
  {
    n = Serial.readStringUntil('\n').toInt();
    Serial.println(n);
    if (n == 0) {
     x=stepper1.currentPosition();
      stepper1.setCurrentPosition(0);
      stepper1.moveTo(0);
    }
    if (n == 1) {
      y=stepper1.currentPosition();
      stepper1.moveTo(5000);
    }
    if (n == 2) {
      y=stepper1.currentPosition();
      stepper1.moveTo(-5000);
    }
  }

  //  if (n == 0) {
  //    stepper1.moveTo(0);;
  //  }
  //  if (n == 1) {
  //    stepper1.moveTo(500);
  //  }
  //  if (n == 2) {
  //    stepper1.moveTo(-3000);
  //  }
  //Change direction when the stepper reaches the target position
//      if (stepper1.distanceToGo() == 0) {
//        stepper1.setCurrentPosition(0);
//      }
  y=stepper1.currentPosition();
  stepper1.run();
  Serial.print(y);
  Serial.print(',');
  Serial.print(x);
  Serial.print(',');
  Serial.println(x-y);
}

