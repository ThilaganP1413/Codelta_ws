
#define stepPin 8
#define dirPin 9

unsigned long lastStepTime = 0;
unsigned long interval = 10000;
int x=1;

bool stepState = false;

void setup() {
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
}
void loop() {
  unsigned long currentMicros = micros();

  if (currentMicros - lastStepTime >= interval) {
    lastStepTime = currentMicros;
    stepState = !stepState;
    digitalWrite(stepPin, stepState);
    Serial.println(x);
    x = x+1;
  }
}
