//turnPage.h
//Program to control swipe and tilt servos for the B.A.T.T. page turning subsystem
//Written by: Andrew Deering
//Trinity University, Engineering Science

//Libraries

//Variables
int SW1 = 11;          //Switch 1 attached to pin 12
int SW2 = 12;          //switch 2 attached to pin 11
const int ledRED = 11; 
const int ledGREEN = 10;
const int ledBLUE = 9;
int swipeDelay = 250;  //350
int tiltDelay = 100;   //200
int tiltPress = 60;    //angle (degrees) for pressing the swipe servo to the screen
int tiltReset = 85;    //angle (degrees) for removing the swipe servo from the screen
int leftStart = 75;
int leftFinish = 130;
int rightStart = 120;
int rightFinish = 60;

//setup
Servo tilt;   //create servo object to control tilt servo
Servo swipe;  // create servo object to control swiping servo

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(ledRED, redValue);
  analogWrite(ledGREEN, greenValue);
  analogWrite(ledBLUE, blueValue);
}

void swipeRight() {
  setColor(0,255,0);
  swipe.write(rightStart);  //set upper left swiper position
  delay(swipeDelay);
  tilt.write(tiltPress);  //move tilt sensor to depress swipe arm ADJUST ANGLE
  delay(tiltDelay);
  swipe.write(rightFinish);  //swipe from upper left to upper right
  delay(swipeDelay);
  tilt.write(tiltReset);  //remove swipe arm from screen
  delay(tiltDelay);
  swipe.write(0);  //move swipe arm to edge of screen
  delay(swipeDelay);
  setColor(0,0,0);
}

void swipeLeft() {
  setColor(255,0,0);
  swipe.write(leftStart);  //set upper right swiper position
  delay(swipeDelay);
  tilt.write(tiltPress);  //move tilt sensor to depress swipe arm ADJUST ANGLE
  delay(tiltDelay);
  swipe.write(leftFinish);  //swipe from upper right to upper left
  delay(swipeDelay);
  tilt.write(tiltReset);  //remove swipe arm from screen
  delay(tiltDelay);
  swipe.write(0);  //move swipe arm to edge of screen
  delay(swipeDelay);
  setColor(0,0,0);
}

void runManual() {         //Uses pushbutton inputs to turn the pages left and rignt
  char instruction = 'D';  //variable to decide page turning direction
  int SW1val = digitalRead(SW1);
  int SW2val = digitalRead(SW2);
  if (SW1val == LOW && SW2val == LOW) {
    instruction = 'N';
  } else if (SW1val == HIGH && SW2val == LOW) {
    instruction = 'L';
  } else if (SW2val == HIGH && SW1val == LOW) {
    instruction = 'R';
  }
  Serial.println(instruction);
  switch (instruction) {  //logic based on inputs received
    case 'L':             //left
      swipeLeft();
      break;
    case 'R':  //right
      swipeRight();
      break;
  }
}

void runTests() {  //Automatically runs the page turner prototype testing
  delay(2000);
  for (int i = 0; i < 20; ++i) {
    setColor(0,0,255);
    swipeLeft();
    setColor(0,0,0);
    delay(500);
  }
  delay(1000);
  setColor(0,0,255);
  delay(200);
  setColor(0,0,0);
  delay(200);
  setColor(0,0,255);
  delay(200);
  setColor(0,0,0);
  delay(200);
  setColor(0,0,255);
  delay(200);
  setColor(0,0,0);
  delay(1000);

  for (int i = 0; i < 20; ++i) {
    setColor(0,0,255);
    swipeRight();
    setColor(0,0,0);
    delay(500);
  }
  int i = 0;
  while (i == 0) {
    setColor(0,0,255);
  }
}