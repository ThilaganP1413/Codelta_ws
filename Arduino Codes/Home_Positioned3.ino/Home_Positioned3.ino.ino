#define stepPin1 12 //violet
#define dirPin1 13 //white

#define stepPin2 10 //brown
#define dirPin2 11 //blue

#define stepPin3 8 //green
#define dirPin3 9 //orange

#define limit1 4
#define limit2 3
#define limit3 2

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

void setup() {
  Serial.begin(9600);  // Initialize serial for debugging

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);

  pinMode(limit1, INPUT_PULLUP);
  pinMode(limit3, INPUT);
  pinMode(limit2, INPUT_PULLUP);

  HomeActuators();
}

void loop() {
    
}

void HomeActuators() {
  Serial.println("Home Positioning");
  bool atHome1 = false;
  bool atHome2 = false;
  bool atHome3 = false;

  unsigned long interval1 = 500;
  unsigned long interval2 = 500;
  unsigned long interval3 = 500;

  // Set directions once (outside loop)
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  digitalWrite(dirPin3, LOW);

  while (!atHome1) {
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
  }

  while (!atHome3) {
    unsigned long currentMicros = micros();
       
    // Motor 3
    if (!atHome3) {
      if (digitalRead(limit3) != HIGH) {
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
  }

  while (!atHome2) {
    unsigned long currentMicros = micros();

    
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
  }
  Serial.println("All Motors Homed");
}
