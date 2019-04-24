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
  if (r > 0) r += 5;
  else r -= 5;
  
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
    int gol = found(LB) ? 40 : -70;
    int gor = found(RB) ? 40 : -70;
    go(gol, gor);
  }
  go(0,0);
}

void setFront() {
  while(!found(LF) || !found(RF)) {
    int gol = found(LF) ? -40 : 70;
    int gor = found(RF) ? -40 : 70;
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
    if (found(LL)) go(120, 100);
    else go(100, 120);
  }
  //go(0,0);
}

void goFWR() {
  while (!found(LF) && !found(RF) && !found(LW)) {
    if (!found(RL)) go(120, 100);
    else go(100, 120);
  }
  //go(0,0);
}

void turnR() {
  go(100, -100);
  delay(340);
  go(0,0);
}

void turnL() {
  go(-100, 100);
  delay(340);
  go(0,0);
}

void setup() {
  pinMode(ML_D, OUTPUT);
  pinMode(MR_D, OUTPUT);

  goFWL();
  goF();
  //goFWR();
  setFront();
  turnL();

  go(80, 80);
  delay(300);
  setBack();
  //goFWR();
  setFront();
  turnR();
  
  //goFWL();
  setFront();
  go(-80, -80);
  delay(150);
  turnR();
  
  setBack();
  //goFWL();
  goF();
  setFront();

  go(0,0);
  delay(100);

  // Checkpoint 1

  setBack();
  go(80, 80);
  delay(200);
  turnR();
  setBack();
  setFront();
}

void loop() {
  //go(200, 200);
  
}
