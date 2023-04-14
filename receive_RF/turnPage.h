
//RGB LED PWM pins on the Arduino UNO
const int ledRED = 11; 
const int ledGREEN = 10;
const int ledBLUE = 9;

//swiping motion configuration cariables
int swipeDelay = 250;  //time in ms that the swipe servo will execute the swiping motion for
int tiltDelay = 100;   //time in ms that the tilt servo will execute the tilting motion for
int tiltPress = 60;    //angle (degrees) for pressing the swipe servo to the screen
int tiltReset = 85;    //angle (degrees) for removing the swipe servo from the screen
int leftStart = 75;    //angle in degrees where the swipe servo will start swiping for turning pages forward
int leftFinish = 130;   //angle in degrees where the swipe servo will stop swiping for turning pages forward
int rightStart = 120;   //angle in degree where the swipe servo will start swiping for turning pages backward
int rightFinish = 60;  //angle in degree where the swipe servo will stop swiping for turning pages backward

//setup
PWMServo tilt;   //create servo object to control tilt servo
PWMServo swipe;  // create servo object to control swiping servo

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(ledRED, redValue);
  analogWrite(ledGREEN, greenValue);
  analogWrite(ledBLUE, blueValue);
}

void swipeRight() {
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
}

void swipeLeft() {
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