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
  // Tune moter
  if (r > 0) r += 3;
  else r -= 8;
  
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
    Go(0,0);
    delay(250);
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
    int gol = found(LB) ? 70 : -70;
    int gor = found(RB) ? 70 : -70;
    go(gol, gor);
  }
  go(0,0);
}

void setFront() {
  while(!found(LF) || !found(RF)) {
    int gol = found(LF) ? -70 : 70;
    int gor = found(RF) ? -70 : 70;
    go(gol, gor);
  }
  go(0,0);
}

void goF() {
  while (!found(LF) && !found(RF) && found(LW) && found(RW)) {
    if (found(LL) && !found(RL)) go(120, 85);
    else if (!found(LL) && found(RL)) go(85, 120);
    else go(100, 100);
  }
  // go(0,0);
}

void goFW() {
  while (!found(LF) && !found(RF)) {
    go(100, 100);
  }
  go(0,0);
}

void goFWL() {
  while (!found(LF) && !found(RF) && !found(RW)) {
    if (found(LL)) go(100, -40);
    else go(-40, 100);
  }
  //go(0,0);
}

void goFWR() {
  while (!found(LF) && !found(RF) && !found(LW)) {
    if (!found(RL)) go(100, -40);
    else go(-40, 100);
  }
  //go(0,0);
}

void turnR() {
  go(120, -120);
  delay(300);
  go(0,0);
}

void turnL() {
  go(-120, 120);
  delay(300);
  go(0,0);
}

void setup() {
  pinMode(ML_D, OUTPUT);
  pinMode(MR_D, OUTPUT);

  delay(500);

  goFWL();
  goF();
  goFWR();
  setFront();
  turnL();

  go(80, 80);
  delay(300);
  setBack();
  goFWL();
  setFront();
  turnR();

  goFWR();
  goF();
  goFWR();
  setFront();
  go(-80, -80);
  delay(150);
  turnR();
  
  setBack();
  goFWL();
  goF();
  setFront();

  go(0,0);
  delay(100);

  // Checkpoint 1

  setBack();
  go(80, 80);
  delay(120);
  turnR(); // 1
  
  setBack();
  setFront();
  turnR(); // 2

  setBack();
  setFront();
  turnL(); // 3

  setBack();
  setFront();
  turnL(); // 4

  setBack();
  setFront();
  turnR(); // 5

  setBack();
  setFront();
  turnR(); // 6

  setBack();
  setFront();
  turnL(); // 7

  setBack();
  setFront();
  turnR(); // 8

  setBack();
  setFront();
  turnL(); // 9

  setBack();
  setFront();
  turnR();
}

void loop() {
  //go(200, 200);
  
}
