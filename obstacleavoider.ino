#include <Servo.h>
int rightSensor = 12;
int leftSensor = 13;
int echo = 9;
int trig = 10;
int time = 0;  // local
long dis = 0;  // local
int md1d = 2;
int md1g = 3;
int md2d = 4;
int md2g = 5;
int right= 12;
int left= 13;
Servo srv;
int i = 0;
int servoPin = 6;
long dr = 0;  //distance to the right
long dl = 0;  //distance to the left
int inLeft , inRight ;
void setup() {
  pinMode(md1d, OUTPUT);
  pinMode(md1g, OUTPUT);
  pinMode(md2d, OUTPUT);
  pinMode(md2g, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(right, INPUT);
  pinMode(left, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(leftSensor, INPUT);  
  pinMode(rightSensor, INPUT);
  srv.attach(servoPin);
  srv.write(0);
  turn(90);
  Serial.begin(9600); 
}
void loop() {
  move();
}



void move_forward() {
  digitalWrite(md1d, HIGH);
  digitalWrite(md1g, LOW);
  digitalWrite(md2d, HIGH);
  digitalWrite(md2g, LOW);
}
void move_backwards() {
  digitalWrite(md1d, LOW);
  digitalWrite(md1g, HIGH);
  digitalWrite(md2d, LOW);
  digitalWrite(md2g, HIGH);
}
void turn_right() {
  digitalWrite(md1d, LOW);
  digitalWrite(md1g, HIGH);
  digitalWrite(md2d, HIGH);
  digitalWrite(md2g, LOW);
}
void turn_left() {
  digitalWrite(md1d, HIGH);
  digitalWrite(md1g, LOW);
  digitalWrite(md2d, LOW);
  digitalWrite(md2g, HIGH);
}
void stop() {
  digitalWrite(md1d, LOW);
  digitalWrite(md1g, LOW);
  digitalWrite(md2d, LOW);
  digitalWrite(md2g, LOW);
}
long calculateDistance(int nmrpinecho, int nmrpintrig) {
  digitalWrite(nmrpintrig, LOW);
  delayMicroseconds(10);
  digitalWrite(nmrpintrig, HIGH);
  delayMicroseconds(2);
  digitalWrite(nmrpintrig, LOW);
  time = pulseIn(nmrpinecho, HIGH);
  dis = 0.0346 * (time) / 2;
  return dis;
}

void turn(int d) {
  for (i; i <= d; i++) {
    srv.write(i);
    delay(10);
  }
}
void re_turn(int d) {
  for (i; i >= d; --i) {
    srv.write(i);
    delay(10);
  }
}
void check_distance() {
  if (dis <= 25) {
    turn(180);
    dr = calculateDistance(echo, trig);
    re_turn(0);
    // delay(30);
    turn(90);
    dl = calculateDistance(echo, trig);
    re_turn(90);
    // delay(30);
  }
}
void move() {
  dis = calculateDistance(echo, trig);

  if (dis > 25) {
    move_forward();
  }

  else {
    stop();   
    check_distance();
    if (dl > dr) {
      turn_left();
      delay(200);
      
    } else if (dr > dl) {
      turn_right();
      delay(200);
    }
    else if(dl <= 10 && dr<=10){
      move_backwards();
      delay(150);
      move();
    }
  }
}