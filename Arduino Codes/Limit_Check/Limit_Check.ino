#define limit1 4
#define limit2 3
#define limit3 2

void setup() {
  Serial.begin(9600);
  pinMode(limit1, INPUT_PULLUP); // Enable internal pull-up resistor
  pinMode(limit2, INPUT_PULLUP);
  pinMode(limit3, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(limit1) == LOW) { // Switch triggered when LOW
    Serial.println("Limit1");
  }
  if (digitalRead(limit2) == LOW) {
    Serial.println("Limit2");
  }
  if (digitalRead(limit3) == LOW) {
    Serial.println("Limit3");
  }
}
