#define stepPin1 13 //violet
#define dirPin1 12 //white

#define stepPin2 10 //brown
#define dirPin2 11 //blue

#define stepPin3 8 //green
#define dirPin3 9 //orange


unsigned long lastStepTime1 = 0;
unsigned long lastStepTime2 = 0;
unsigned long lastStepTime3 = 0;

unsigned long interval1 = 500;
unsigned long interval2 = 500;
unsigned long interval3 = 500;

bool stepState1 = false;
bool stepState2 = false;
bool stepState3 = false;

int currenPos1 = 0;
int currentPos2 = 0;
int currentPos3 = 0;

int Positions[][3] = {{7964,7964,7964},
                       {7000,7000,7000},
                       {5543,7964,2030},
                       {0,0,0}
                      };

void Actuate(int list[]);

void setup() {
  
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  
}

void loop() {
  unsigned long currentMicros = micros();

  for i[] in Positions[][3]{
    Actuate(int i[]);
  }
  
}

void Actuate (int list[]){

  while currentPos1 != list[0]{

    if currentPos1 < list[0] {

      if (currentMicros - lastStepTime1 >= interval1) {
        digitalWrite(dirPin1, HIGH);
        lastStepTime1 = currentMicros;
        stepState1 = !stepState1;
        digitalWrite(stepPin1, stepState1);
        currentPos1 ++ ;
      }

    }

    else{
      
      if (currentMicros - lastStepTime1 >= interval1) { 
        digitalWrite(dirPin1, LOW);
        lastStepTime1 = currentMicros;
        stepState1 = !stepState1;
        digitalWrite(stepPin1, stepState1);
        currentPos1 -- ;
      }
    }
  }

  while currentPos2 != list[1]{
    
    if currentPos2 < list[1] {

      if (currentMicros - lastStepTime2 >= interval2) {
        digitalWrite(dirPin2, HIGH);
        lastStepTime2 = currentMicros;
        stepState2 = !stepState1;
        digitalWrite(stepPin2, stepState2);
        currentPos2 ++ ;
      }

    }

    else{
      
      if (currentMicros - lastStepTime2 >= interval2) { 
        digitalWrite(dirPin2, LOW);
        lastStepTime2 = currentMicros;
        stepState1 = !stepState2;
        digitalWrite(stepPin2, stepState2);
        currentPos2 -- ;
      }
    }
  }

  
  while currentPos3 != list[2]{
    
    if currentPos3 < list[2] {

      if (currentMicros - lastStepTime3 >= interval3) {
        digitalWrite(dirPin3, HIGH);
        lastStepTime3 = currentMicros;
        stepState3 = !stepState3;
        digitalWrite(stepPin3, stepState3);
        currentPos3 ++ ;
      }

    }

    else{
      
      if (currentMicros - lastStepTime3 >= interval3) {
        digitalWrite(dirPin3, LOW);
        lastStepTime3 = currentMicros;
        stepState3 = !stepState3;
        digitalWrite(stepPin3, stepState3);
        currentPos3 -- ;
      }
    }
  }

}
