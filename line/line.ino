#define ML_D 8
#define ML_S 9
#define MR_S 10
#define MR_D 11

#define SC 0
#define SR 1
#define SL 2

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
  }
  Go(l, r);
  oldL = l;
  oldR = r;
}

bool found(int port) {
  return analogRead(port) > 512;
}

void track() {
  while (!found(SL)) {
    if (found(SC) && !found(SR)) go(70,150);
    else if (!found(SC) && found(SR)) go(150, 70);
    else go(110, 110);
  }
}

void setup() {
  pinMode(ML_D, OUTPUT);
  pinMode(MR_D, OUTPUT);

  // track();
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 5; i++) {
    track();
    delay(150);
  }
  go(0, 0);
  delay(500);
}
