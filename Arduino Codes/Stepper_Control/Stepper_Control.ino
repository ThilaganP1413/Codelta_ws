#define stepPin1 8
#define dirPin1 9
//
//#define stepPin2 12
//#define dirPin2 11
//
//#define stepPin3 7
//#define dirPin3 6

unsigned long lastStepTime1 = 0;
//unsigned long lastStepTime2 = 0;
//unsigned long lastStepTime3 = 0;

unsigned long interval1 = 500;  // speed for motor 1
//unsigned long interval2 = 500;   // speed for motor 2
//unsigned long interval3 = 2000;  // speed for motor 3

bool stepState1 = false;
//bool stepState2 = false;
//bool stepState3 = false;

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  digitalWrite(dirPin1, HIGH);
//
//  pinMode(stepPin2, OUTPUT);
//  pinMode(dirPin2, OUTPUT);
//  digitalWrite(dirPin2, HIGH);
//
//  pinMode(stepPin3, OUTPUT);
//  pinMode(dirPin3, OUTPUT);
//  digitalWrite(dirPin3, HIGH);
}

void loop() {
  unsigned long currentMicros = micros();

  // Motor 1
  if (currentMicros - lastStepTime1 >= interval1) {
    lastStepTime1 = currentMicros;
    stepState1 = !stepState1;
    digitalWrite(stepPin1, stepState1);
  }

//  // Motor 2
//  if (currentMicros - lastStepTime2 >= interval2) {
//    lastStepTime2 = currentMicros;
//    stepState2 = !stepState2;
//    digitalWrite(stepPin2, stepState2);
//  }
//
//  // Motor 3
//  if (currentMicros - lastStepTime3 >= interval3) {
//    lastStepTime3 = currentMicros;
//    stepState3 = !stepState3;
//    digitalWrite(stepPin3, stepState3);
//  }
}
