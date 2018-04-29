
//============ Change these for each robot
const int LF = 5;          // Left Motor Forward
const int LR = 4;          // Left Motor Reverse
const int RF = 7;          // Right Motor Reverse
const int RR = 6;          // Right  Motor Reverse
const int RE = 9;        // Right Encoder
const int LE = 8;        // Right Encoder

//============
int Sp = .9 * 255;
int TSp = .55 * 255;
boolean CDir = false;
int LEVal = 0;
int REVal = 0;
int LELast = 0;
int RELast = 0;
int LEState = 0;
int REState = 0;
int x;
int y;
int Case;
boolean DriveComp = false;
int CurAngle = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);
  pinMode(RE, INPUT);
  pinMode(LE, INPUT);

}


void loop() {
  //   while (Serial.available()){
  //     int Case = Serial.readStringUntil('\n').toInt();
  //     }
  //  encoder();
  while (DriveComp == false) {
    drive(0, Case);
    while (Serial1.available()) {
      Case = Serial1.readStringUntil('\n').toInt();
    }
  }
  delay(1500);
  DriveComp = false;
  CDir = false;
}

void drive(int Dist, int Angle) {
  encoder();
  if (CDir == false) {
    if (Angle == 0) {
      CDir = true;
    }
    if (CurAngle != Angle) {
      if (Angle > 0) {
        CurAngle = ((REVal + LEVal) / 2);
        if (LEVal == REVal) {
          analogWrite(LF, TSp);
          analogWrite(RR, TSp);
          analogWrite(LR, 0);
          analogWrite(RF, 0);
          debug();
        }
        if (LEVal < REVal) {
          analogWrite(LF, TSp);
          analogWrite(RR, (TSp * .8));
          analogWrite(LR, 0);
          analogWrite(RF, 0);
        }
        if (LEVal > REVal) {
          analogWrite(LF, (TSp * .8));
          analogWrite(RR, TSp);
          analogWrite(LR, 0);
          analogWrite(RF, 0);
        }
      }
      if (Angle < 0) {
        CurAngle = -1 * ((REVal + LEVal) / 2);
        if (LEVal == REVal) {
          analogWrite(LR, TSp);
          analogWrite(RF, TSp);
          analogWrite(LF, 0);
          analogWrite(RR, 0);
          debug();
        }
        if (LEVal < REVal) {
          analogWrite(LR, TSp);
          analogWrite(RF, (TSp * .8));
          analogWrite(LF, 0);
          analogWrite(RR, 0);
        }
        if (LEVal > REVal) {
          analogWrite(LR, (TSp * .8));
          analogWrite(RF, TSp);
          analogWrite(LF, 0);
          analogWrite(RR, 0);
        }
      }
    }
    if (CurAngle == Angle) {
      motorOff();
      LEVal = 0;
      REVal = 0;
      CurAngle=0;
      CDir = true;
    }
  }
  if (CDir == true) {
    if (LEVal < Dist || REVal < Dist) {
      if (LEVal == REVal) {
        analogWrite(LF, Sp);
        analogWrite(RF, Sp);
        analogWrite(LR, 0);
        analogWrite(RR, 0);
        debug();
      }
      if (LEVal < REVal) {
        analogWrite(LF, Sp);
        analogWrite(RF, (Sp * .8));
        analogWrite(LR, 0);
        analogWrite(RR, 0);
      }
      if (LEVal > REVal) {
        analogWrite(LF, Sp * .8);
        analogWrite(RF, Sp);
        analogWrite(LR, 0);
        analogWrite(RR, 0);
      }
    }

    if (LEVal >= Dist) {
      analogWrite(LF, 0);
      analogWrite(LR, 0);
    }
    if (REVal >= Dist) {
      analogWrite(RF, 0);
      analogWrite(RR, 0);
    }
    if (LEVal >= Dist && REVal >= Dist) {
      LEVal = 0;
      REVal = 0;
      DriveComp = true;
    }
  }
}


void debug() {
  Serial.print("<");
  Serial.print(Case);
  Serial.print(",");
  Serial.print(CurAngle);
  Serial.print(",");
  Serial.print(LEVal);
  Serial.print(",");
  Serial.print(REVal);
  Serial.println(">");
}

void motorOff() {
  analogWrite(LF, 0);                      // turn off left motor
  analogWrite(LR, 0);                      // turn off right motor
  analogWrite(RF, 0);                      // turn off left motor
  analogWrite(RR, 0);                      // turn off right motor
}

void encoder() {
  LEState = digitalRead(LE);
  REState = digitalRead(RE);
  if (LEState != LELast) {
    LEVal = LEVal + 1;
  }
  if (REState != RELast) {
    REVal = REVal + 1;
  }
  LELast = LEState;
  RELast = REState;
  debug();
}








