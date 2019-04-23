#define ML_D 8
#define ML_S 9
#define MR_S 10
#define MR_D 11

#define LF 5
#define LW 6
#define LL 7
#define LB 12

#define RF 2
#define RW 3
#define RL 4
#define RB 13


void Go(int l, int r) {
  digitalWrite(ML_D, l < 0);
  analogWrite (ML_S, l < 0 ? 255 + l : l);
  digitalWrite(MR_D, r < 0);
  analogWrite (MR_S, r < 0 ? 255 + r : r);
}

int oldL;
int oldR;

void go(int l, int r) {
  if (l == 0 && r == 0) {
    Go(-oldL, -oldR);
    delay(50); 
  }
  Go(l, r);
  oldL = l;
  oldR = r;
}

bool found(int port) {
  return !digitalRead(port);
}

void setBack() {
  while(!found(LB) || !found(RB)) {
    int gol = found(LB) ? 20 : -100;
    int gor = found(RB) ? 20 : -100;
    go(gol, gor);
  }
  go(0,0);
}

void setFront() {
  while(!found(LF) || !found(RF)) {
    int gol = found(LF) ? -20 : 100;
    int gor = found(RF) ? -20 : 100;
    go(gol, gor);
  }
  go(0,0);
}

void goF() {
  while (!found(LF) && !found(RF) && found(LW) && found(RW)) {
    if (found(LL) && !found(RL)) go(130, 80);
    else if (!found(LL) && found(RL)) go(80, 130);
    else go(100, 100);
  }
  go(0,0);
}

void goFW() {
  while (!found(LF) && !found(RF)) {
    if (found(LL) && !found(RL)) go(130, 80);
    else if (!found(LL) && found(RL)) go(80, 130);
    else go(100, 100);
  }
  go(0,0);
}

void goFuWR() {
  while(!found(LW)) go(100, 100);
  go(0,0);
}

void turnR() {
  go(100, -100);
  delay(350);
  go(0,0);
}

void turnL() {
  go(-100, 100);
  delay(350);
  go(0,0);
}

void setup() {
  pinMode(ML_D, OUTPUT);
  pinMode(MR_D, OUTPUT);

  goFuWR();
  goF();
  goFW();
  turnL();
  setBack();
  setFront();
  go(-100, -100);
  delay(150);
  turnR();
  setFront();
  turnR();
  setBack();
  goFuWR();
  setFront();

  setBack();
  go(100, 100);
  delay(200);
  turnR();
  setBack();
}

void loop() {
  //go(200, 200);
  
}
