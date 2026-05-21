const int capPin = A0;
unsigned long startTime = 0;
bool measuring = false;
bool armed = false;   // capacitor confirmed discharged
const float threshold = 0.05;           // ~0 V
const unsigned long maxTime = 120000;    // 15 s ≈ 5τ
void setup() {
  Serial.begin(9600);
  Serial.println("Time_ms,Voltage_V");
}
void loop() {
  float voltage = analogRead(capPin) * (5.0 / 1023.0);
  if (voltage < threshold) {
    measuring = false;
    armed = true;       // ready for next run
    delay(50);          // debounce / noise filter
    return;
  }
  if (!measuring && armed && voltage >= threshold) {
    startTime = millis();
    measuring = true;
    armed = false;

    Serial.println("START");
    Serial.println("Time_ms,Voltage_V");
  }
  if (measuring) {
    unsigned long t = millis() - startTime;
    Serial.print(t);
    Serial.print(",");
    Serial.println(voltage, 3);
    if (t >= maxTime) {
      measuring = false;
    }
    delay(20); // 50 Hz sampling
  }
}
