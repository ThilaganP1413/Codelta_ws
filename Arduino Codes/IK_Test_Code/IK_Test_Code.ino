#define stepPin1 5 //violet
#define dirPin1 12 //white
#define stepPin2 4 //brown
#define dirPin2 11 //blue
#define stepPin3 6 //green
#define dirPin3 10 //orange

unsigned long lastStepTime1 = 0;
unsigned long lastStepTime2 = 0;
unsigned long lastStepTime3 = 0;
unsigned long interval1 = 500;
unsigned long interval2 = 500;
unsigned long interval3 = 500;

bool stepState1 = false;
bool stepState2 = false;
bool stepState3 = false;

int currentPos1 = 0;
int currentPos2 = 0;
int currentPos3 = 0;

int targetPos1 = 0;
int targetPos2 = 0;
int targetPos3 = 0;

const int PACKET_SIZE = 3;
byte Position[PACKET_SIZE];

bool newPos = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
}

void loop() {
  // Check for new serial data
  receivePacket();
  
  // If new positions received
  if (newPos) {
    targetPos1 = Position[0];
    targetPos2 = Position[1];
    targetPos3 = Position[2];
    newPos = false;
    Serial.print("New targets: ");
    Serial.print(targetPos1);
    Serial.print(", ");
    Serial.print(targetPos2);
    Serial.print(", ");
    Serial.println(targetPos3);
  }

  // Control motors continuously
  Actuate();
}

void receivePacket() {
  static bool receiving = false;
  static byte idx = 0;
  
  while (Serial.available() > 0) {
    byte inByte = Serial.read();

    if (inByte == 0xFF) {
      receiving = true;
      idx = 0;
    }
    else if (receiving && idx < PACKET_SIZE) {
      Position[idx] = inByte;
      idx++;

      if (idx >= PACKET_SIZE) {
        receiving = false;
        newPos = true;
      }
    }
  }
}

void Actuate() {
  unsigned long currentMicros = micros();
  
  // Motor 1 control
  if (currentPos1 != targetPos1) {
    if (currentPos1 < targetPos1) {
      if (currentMicros - lastStepTime1 >= interval1) {
        digitalWrite(dirPin1, HIGH);
        lastStepTime1 = currentMicros;
        stepState1 = !stepState1;
        digitalWrite(stepPin1, stepState1);
        currentPos1++;
      }
    } else {
      if (currentMicros - lastStepTime1 >= interval1) { 
        digitalWrite(dirPin1, LOW);
        lastStepTime1 = currentMicros;
        stepState1 = !stepState1;
        digitalWrite(stepPin1, stepState1);
        currentPos1--;
      }
    }
  }
  
  // Motor 2 control
  if (currentPos2 != targetPos2) {
    if (currentPos2 < targetPos2) {
      if (currentMicros - lastStepTime2 >= interval2) {
        digitalWrite(dirPin2, HIGH);
        lastStepTime2 = currentMicros;
        stepState2 = !stepState2;
        digitalWrite(stepPin2, stepState2);
        currentPos2++;
      }
    } else {
      if (currentMicros - lastStepTime2 >= interval2) { 
        digitalWrite(dirPin2, LOW);
        lastStepTime2 = currentMicros;
        stepState2 = !stepState2; 
        digitalWrite(stepPin2, stepState2);
        currentPos2--;
      }
    }
  }
  
  // Motor 3 control
  if (currentPos3 != targetPos3) {
    if (currentPos3 < targetPos3) {
      if (currentMicros - lastStepTime3 >= interval3) {
        digitalWrite(dirPin3, HIGH);
        lastStepTime3 = currentMicros;
        stepState3 = !stepState3;
        digitalWrite(stepPin3, stepState3);
        currentPos3++;
      }
    } else {
      if (currentMicros - lastStepTime3 >= interval3) {
        digitalWrite(dirPin3, LOW);
        lastStepTime3 = currentMicros;
        stepState3 = !stepState3;
        digitalWrite(stepPin3, stepState3);
        currentPos3--;
      }
    }
  }
}
