const int potPin = A0;
const int btnUp = 8;         // Normal mode: cycle LED modes
const int btnDown = 7;       // Normal mode: cycle LED modes
const int btnEmergency = 12; // Toggle emergency mode
const int ledPins[4] = {2, 3, 4, 5};  
const int buzzerPin = 6;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
int threatLevel = 0;
int responseLevel = 0;       
bool emergencyActive = false;
bool upPressed = false;
bool downPressed = false;
bool emergencyLast = LOW;    // for toggle detection
void setup() {
  for (int i = 0; i < 4; i++)
    pinMode(ledPins[i], OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnEmergency, INPUT_PULLUP);
  digitalWrite(ledPins[0], HIGH);
  setRGB(0, 0, 255);  // Safe (blue)
}
void loop() {
  bool emergencyNow = digitalRead(btnEmergency);
  if (emergencyNow == HIGH && emergencyLast == LOW) {
    emergencyActive = !emergencyActive;
    if (!emergencyActive) {
      responseLevel = 0;      // Back to LED pin 2 (Normal)
      setRGB(0, 0, 255);      // Reset RGB to safe color
      noTone(buzzerPin);      // Stop any buzzer tone
    }
  }
  emergencyLast = emergencyNow;
  if (emergencyActive) {
    handleEmergency();
    return;
  }
  readThreat();
  updateThreatRGB();
  autoBuzzer();
  handleButtonsNormal();
  updateLEDsNormal();
}
void handleEmergency() {
  setRGB(0, 0, 0);
  for (int i = 0; i < 4; i++)
    digitalWrite(ledPins[i], LOW);
  digitalWrite(ledPins[3], HIGH);  // Emergency LED ON
  tone(buzzerPin, 300);  // Low continuous tone
}
void readThreat() {
  int pot = analogRead(potPin);

  if (pot <= 250) threatLevel = 0;
  else if (pot <= 500) threatLevel = 1;
  else if (pot <= 750) threatLevel = 2;
  else threatLevel = 3;
}
void updateThreatRGB() {
  switch (threatLevel) {
    case 0: setRGB(0, 0, 255); break;       // Blue
    case 1: setRGB(0, 255, 0); break;       // Green
    case 2: setRGB(255, 255, 0); break;     // Yellow
    case 3: setRGB(255, 0, 0); break;       // Red
  }
}
void setRGB(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
void autoBuzzer() {
  if (threatLevel < 2) {
    noTone(buzzerPin);
    return;
  }
  if (threatLevel == 2) {
    static unsigned long lastToggle = 0;
    static bool on = false;
    if (millis() - lastToggle > 300) {
      lastToggle = millis();
      on = !on;
      if (on) tone(buzzerPin, 1000);
      else noTone(buzzerPin);
    }
  }
  if (threatLevel == 3) {
    tone(buzzerPin, 1000);  // continuous high tone
  }
}
void handleButtonsNormal() {
  if (digitalRead(btnUp) == LOW && !upPressed) {
    upPressed = true;
    if (responseLevel < 2) responseLevel++;  // Only 0–2 allowed
  }
  if (digitalRead(btnUp) == HIGH) upPressed = false;
  if (digitalRead(btnDown) == LOW && !downPressed) {
    downPressed = true;
    if (responseLevel > 0) responseLevel--;
  }
  if (digitalRead(btnDown) == HIGH) downPressed = false;
}
void updateLEDsNormal() {
  for (int i = 0; i < 4; i++)
    digitalWrite(ledPins[i], LOW);
  digitalWrite(ledPins[responseLevel], HIGH);
}