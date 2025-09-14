#define stepPin2 12 //violet
#define dirPin2 13 //white

#define stepPin3 10 //brown
#define dirPin3 11 //blue

#define stepPin1 8 //green
#define dirPin1 9 //orange

#define limit2 4
#define limit3 3
#define limit1 2

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

void HomeActuators();

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
  Serial.begin(9600);  // Initialize serial for debugging

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);

  pinMode(limit1, INPUT_PULLUP);
  pinMode(limit2, INPUT_PULLUP);
  pinMode(limit3, INPUT_PULLUP);

  HomeActuators();
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

void HomeActuators() {
  Serial.println("Home Positioning");
  bool atHome = false;
  bool atHome1 = false;
  bool atHome2 = false;
  bool atHome3 = false;

  unsigned long interval2 = 700;

  // Set directions once (outside loop)
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  digitalWrite(dirPin3, LOW);

  while (!atHome) {
    unsigned long currentMicros = micros();
    
    // Motor 1
    if (!atHome1) {
      if (digitalRead(limit1) != LOW) {  // Not pressed
        if (currentMicros - lastStepTime1 >= interval1) {
          lastStepTime1 = currentMicros;
          stepState1 = !stepState1;
          digitalWrite(stepPin1, stepState1);
        }
      } 
      else {  // Pressed
        atHome1 = true;
        Serial.println("Motor1 Homed");
        currentPos1 = 0;
      }
    }

    // Motor 3
    if (!atHome3) {
      if (digitalRead(limit3) != LOW) {
        if (currentMicros - lastStepTime3 >= interval3) {
          lastStepTime3 = currentMicros;
          stepState3 = !stepState3;
          digitalWrite(stepPin3, stepState3);
        }
      }
      else {
        atHome3 = true;
        Serial.println("Motor3 Homed");
        currentPos3 = 0;
      }
    }

    // Motor 2
    if (!atHome2) {
      if (digitalRead(limit2) != LOW) {
        if (currentMicros - lastStepTime2 >= interval2) {
          lastStepTime2 = currentMicros;
          stepState2 = !stepState2;
          digitalWrite(stepPin2, stepState2);
        }
      } 
      else {
        atHome2 = true;
        Serial.println("Motor2 Homed");
        currentPos2 = 0;
      }
    }

    atHome = atHome1 && atHome2 && atHome3;
  }
  Serial.println("All Motors Homed");
}
