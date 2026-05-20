const int led[8] = {2,3,4,5,6,7,8,9};
const int buttonpin1 = 10;
const int buttonpin2 = 11;

const int delaytime1 = 500;
const int delaytime2 = 200;

void setup() {
  for(int i = 0; i<=7; i++){
    pinMode(led[i], OUTPUT);
  }
  pinMode(buttonpin1, INPUT_PULLUP);
  pinMode(buttonpin2, INPUT_PULLUP);
}

void loop() {
  int buttonState1 = digitalRead(buttonpin1);
  int buttonState2 = digitalRead(buttonpin2);
  if(buttonState1== HIGH){
    for(int i = 0; i<3; i++){
        runSequence(delaytime1);
    }
    low();
  }
  else if(buttonState2 == HIGH){
    for(int i = 0; i<3; i++){
        runSequence(delaytime2);
    }
    low();
  }

}


void runSequence(int time){
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
    delay(time);
  }
}

void low(){
  for(int i = 0; i <=7; i++){
    digitalWrite(led[i],LOW);
  }
}
