#include <Servo.h>
int hand = 13;
int eyes = 12;
int button = 22;
int red = 52;
int green = 50;
int buzzer = 23;
int trigPin = 31;
int echoPin = 30;
// set the IO pin for each segment
int a = 7;   // set digital pin 7 for segment a
int b = 6;   // set digital pin 6 for segment b
int c = 5;   // set digital pin 5 for segment c
int d = 10;  // set digital pin 10 for segment d
int e = 11;  // set digital pin 11 for segment e
int f = 8;   // set digital pin 8 for segment f
int g = 9;   // set digital pin 9 for segment g
int dp = 4;  // set digital pin 4 for segment dp


int hangle, hpulsewidth;  //
int eangle, epulsewidth;
int second = 0;
long duration, currentD=0, pDistance=0;  // Duration used to calculate distance
int state = HIGH;      // the current state of the output pin
int buttonState;// the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
const int sensitivity = 2;
bool gameOver = false;
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed

void handpulse(int hand, int hangle)  // funtction for hand
{
  hpulsewidth = (hangle * 11) + 500;  // convert angle to 500-2480 pulse width
  digitalWrite(hand, HIGH);           // set the level of servo pin as “high”
  delayMicroseconds(hpulsewidth);     // delay microsecond of pulse width
  digitalWrite(hand, LOW);            // set the level of servo pin as “low”
  delay(20 - hpulsewidth / 1000);
}

void eyepulse(int eyes, int eangle)  // funtction for servo w/ ultrasonic sensor
{
  epulsewidth = (eangle * 11) + 500;  // convert angle to 500-2480 pulse width
  digitalWrite(eyes, HIGH);           // set the level of servo pin as “high”
  delayMicroseconds(epulsewidth);     // delay microsecond of pulse width
  digitalWrite(eyes, LOW);            // set the level of servo pin as “low”
  delay(20 - epulsewidth / 1000);
}
void digital_0(void)  // display number 5
{
  unsigned char j;
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}
void digital_1(void)  // display number 1
{
  unsigned char j;
  digitalWrite(c, HIGH);     // set level as “high” for pin 5, turn on segment c
  digitalWrite(b, HIGH);     // turn on segment b
  for (j = 7; j <= 11; j++)  // turn off other segments
    digitalWrite(j, LOW);
  digitalWrite(dp, LOW);  // turn off segment dp
}
void digital_2(void)  // display number 2
{
  unsigned char j;
  digitalWrite(b, HIGH);
  digitalWrite(a, HIGH);
  for (j = 9; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(c, LOW);
  digitalWrite(f, LOW);
}
void digital_3(void)  // display number 3
{
  digitalWrite(g, HIGH);
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(f, LOW);
  digitalWrite(e, LOW);
}
void digital_4(void)  // display number 4
{
  digitalWrite(c, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(a, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
}
void digital_5(void)  // display number 5
{
  unsigned char j;
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}
void digital_6(void)  // display number 6
{
  unsigned char j;
  for (j = 7; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(b, LOW);
}
void digital_7(void)  // display number 7
{
  unsigned char j;
  for (j = 5; j <= 7; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  for (j = 8; j <= 11; j++)
    digitalWrite(j, LOW);
}
void digital_8(void)  // display number 8
{
  unsigned char j;
  for (j = 5; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
}
void digital_9(void)  // display number 5
{
  unsigned char j;
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void eliminate(void) {
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  {
    handpulse(hand, 180);
  }
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  {
    handpulse(hand, 0);
  }
  gameOver=true;
}

void checkServo(void) {
  tone(buzzer, 784);
  digitalWrite(red, HIGH);
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  { eyepulse(eyes, 0);}
  pDistance = measureDistance();
  detect();
  digitalWrite(red, LOW);
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  {eyepulse(eyes, 180);}
  
}

void resetGame(void) {
  digitalWrite(red, LOW);    // turn off red LED
  digitalWrite(green, LOW);  // turn off green LED
  noTone(buzzer);
  //turn the servo for lone player away
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  {eyepulse(eyes, 180);}

//move the arm back to restart position
  for (int i = 0; i <= 50; i++)  // giving the servo time to rotate to commanded position
  { handpulse(hand, 0);}
  //gameOver = false;

}

void displaySeg(int second) {
  if (second == 6) {
    digital_6();}
  else if (second == 5) {
    digital_5();}
  else if (second == 4) {
    digital_4();}
  else if (second == 3) {
    digital_3();}
  else if (second == 2) {
    digital_2();}
  else if (second == 1) {
    digital_1();}
  else if (second == 0) {
    digital_0();}

}

void detect(void) {
   
  currentD = measureDistance();
  //check for 3 sec
  for (int i = 0; i < 60; i++) {
     currentD = measureDistance();
     Serial.print("currentD ");
      Serial.println(currentD);
      Serial.print("pDistance ");
      Serial.println(pDistance);

    if (abs(currentD - pDistance) >= sensitivity ) {
      Serial.println("player detected");
      eliminate();
      resetGame();
    }
    if(gameOver == true){
      return;
    }
    pDistance = currentD;
    delay(50);
  }
}

void setup() {
  Serial.begin(9600);       // connect to serial port, set baud rate at “9600”
  pinMode(hand, OUTPUT);    // set servo pin as “output”
  pinMode(eyes, OUTPUT);    // set servo pin as “output”
  pinMode(buzzer, OUTPUT);  // set servo buzzer as “output”
  pinMode(button, INPUT);   // set button pin as “input”
  pinMode(red, OUTPUT);     // set servo redled as “output”
  pinMode(green, OUTPUT);
  pinMode(echoPin, INPUT);  // set servo redled as “output”
  pinMode(trigPin, OUTPUT);
  for (int i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT);  // set pin 4-11as “output”
  }
  resetGame();
  buttonState = digitalRead(button); //read button input
}

int measureDistance() {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  int dis = duration / 58.2;
  //still need to figure out getting rid of bad data
  if (dis >= maximumRange) {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

  int dis = duration / 58.2;
  }
  return dis;
}

void playerMov(void){
  tone(buzzer, 440);
  digitalWrite(green, HIGH);
  delay(2000);
  digitalWrite(green, LOW);
}

void loop() {
  gameOver = false;
  previous =  buttonState; // read button input
  buttonState = digitalRead(button); 
  noTone(buzzer);
  if (previous == HIGH && buttonState == LOW) {
    Serial.println("GameStart");
    int j = 6;
    while(gameOver != true && j >= 0 ){
       if(j == 0){
        displaySeg(j);
        eliminate();
        break;
      }
      Serial.println(j);
      displaySeg(j);
      playerMov();
      checkServo();
      j--;
   
    }
    if(gameOver == true){
      Serial.println("gameOVer");
    }
  
   
  }
}
