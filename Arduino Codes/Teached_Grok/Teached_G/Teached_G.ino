#define stepPin1 12 //violet
#define dirPin1 13 //white

#define stepPin2 10 //brown
#define dirPin2 11 //blue

#define stepPin3 8 //green
#define dirPin3 9 //orange

#define limit1 4
#define limit2 3
#define limit3 2

#define suction 5
#define conveyor 7

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

int Positions[][3] = {{1100,5610, 5124},
                      {4512, 2000, 500},
                      {3456, 5244, 3000},
                      {1254, 500, 2200},
                      {5984, 4510, 2380},
                      {0, 0, 0}
                     };

int numPositions = 6;  // Number of position arrays
int currentPositionIndex = 0;
bool movementComplete = false;

void Actuate(int list[]);

void setup() {
  Serial.begin(9600);  // Added for debugging
  
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
}

void loop() {

  if (!movementComplete) {
    Actuate(Positions[currentPositionIndex]);
    
    if (currentPos1 == Positions[currentPositionIndex][0] && 
        currentPos2 == Positions[currentPositionIndex][1] && 
        currentPos3 == Positions[currentPositionIndex][2]) {
      
      currentPositionIndex++;
      if (currentPositionIndex >= numPositions) {
        currentPositionIndex = 0;
        movementComplete = true;
        Serial.println("All positions completed!");
      }
    }
  }
}

void Actuate(int list[]) {
  unsigned long currentMicros = micros();  // Moved inside function
  
  // Motor 1 control
  if (currentPos1 != list[0]) {
    if (currentPos1 < list[0]) {
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
  if (currentPos2 != list[1]) {
    if (currentPos2 < list[1]) {
      if (currentMicros - lastStepTime2 >= interval2) {
        digitalWrite(dirPin2, HIGH);
        lastStepTime2 = currentMicros;
        stepState2 = !stepState2;  // Fixed: was !stepState1
        digitalWrite(stepPin2, stepState2);
        currentPos2++;
      }
    } else {
      if (currentMicros - lastStepTime2 >= interval2) { 
        digitalWrite(dirPin2, LOW);
        lastStepTime2 = currentMicros;
        stepState2 = !stepState2;  // Fixed: was stepState1 = !stepState2
        digitalWrite(stepPin2, stepState2);
        currentPos2--;
      }
    }
  }
  
  // Motor 3 control
  if (currentPos3 != list[2]) {
    if (currentPos3 < list[2]) {
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
