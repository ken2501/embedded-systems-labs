const int led[8] = {2,3,4,5,6,7,8,9};
const int buttonpin1 = 10;

void setup() {
  for(int i = 0; i<=7; i++){
    pinMode(led[i], OUTPUT);
  }
  pinMode(buttonpin1, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(buttonpin1)== HIGH){
    for(int i = 0; i<3; i++){
      runSequence();
    }
    low();
  }
}


void runSequence(){
   int steps[][8] = {
    {1,0,0,0,0,0,0,0}, {1,1,0,0,0,0,0,0}, {1,1,1,0,0,0,0,0}, {0,1,1,1,0,0,0,0},
    {0,0,1,1,1,0,0,0}, {0,0,0,1,1,1,0,0}, {0,0,0,0,1,1,1,0}, {0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1}, {0,0,0,0,0,0,0,1}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,1}, {0,0,0,0,0,1,1,1}, {0,0,0,0,1,1,1,0}, {0,0,0,1,1,1,0,0},
    {0,0,1,1,1,0,0,0}, {0,1,1,1,0,0,0,0}, {1,1,1,0,0,0,0,0}, {1,1,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}
  };

  for (int s = 0; s < 22; s++) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(led[i], steps[s][i]);
    }
    delay(500);
  }
}

void low(){
  for(int i = 0; i <=7; i++){
    digitalWrite(led[i],LOW);
  }
}
