#include <Servo.h>


const int onboardLed = 13;
const int extLed = 3;
unsigned long past = 0;

Servo myservo;

bool blinkstate = false;


void setup() {
  Serial.begin(9600);

  pinMode(onboardLed, OUTPUT);
  pinMode(extLed, OUTPUT);


  myservo.attach(5);

  digitalWrite(onboardLed, HIGH);
  analogWrite(extLed, 255);

  Serial.println("Startup: LEDs ON (3s)");
  delay(3000);

  digitalWrite(onboardLed, LOW);
  analogWrite(extLed, 0);
  Serial.println("Startup: LEDs OFF, starting servo sequence");


  myservo.write(0);
  Serial.println("Servo ---> 0");
  delay(1000);

  myservo.write(45);
  Serial.println("Servo ---> 45 (Waiting 3s)");
  delay(3000);

  myservo.write(125);
  Serial.println("Servo ---> 125 (2s)");
  delay(2000);

  Serial.println("Entering Main Sequence");
}

void loop() {
  int raw = analogRead(A0);
  float voltage = raw * (5.0/1023.0);
  Serial.print("A0 raw=");
  Serial.print(raw);
  Serial.print("  V=");
  Serial.println(voltage, 3);

  if(voltage>2.5){
    unsigned long now = millis();

    if(now-past >= 400){
      past = now;
      blinkstate=!blinkstate;
      digitalWrite(onboardLed, blinkstate ? HIGH : LOW);
    } 
  }else if (voltage <= 2.5 && voltage >= 2.0){
    digitalWrite(onboardLed,LOW);
  } else if (voltage >=1.0 && voltage < 2.0){
    digitalWrite(onboardLed, HIGH);
  } else{
    digitalWrite(onboardLed, LOW);
  }

  if (raw <= 2) {
    analogWrite(extLed, 0);
    myservo.write(0);
  } else if (raw>=1021){
    analogWrite(extLed, 255);
    myservo.write(180);
  } else{
    int pwm = map(raw, 0, 1023, 0, 255);
    int angle = map(raw, 0, 1023, 0, 180);


    analogWrite(extLed,pwm);
    myservo.write(angle);
  }
}