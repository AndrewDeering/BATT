//swiping motion configuration cariables
int swipeDelay = 250;  //time in ms that the swipe servo will execute the swiping motion for
int tiltDelay = 100;   //time in ms that the tilt servo will execute the tilting motion for
int tiltPress = 60;    //angle (degrees) for pressing the swipe servo to the screen
int tiltReset = 85;    //angle (degrees) for removing the swipe servo from the screen
int leftStart = 75;    //angle in degrees where the swipe servo will start swiping for turning pages forward
int leftFinish = 130;   //angle in degrees where the swipe servo will stop swiping for turning pages forward
int rightStart = 120;   //angle in degree where the swipe servo will start swiping for turning pages backward
int rightFinish = 60;  //angle in degree where the swipe servo will stop swiping for turning pages backward
const int swipeLeftPin = 11;
const int swipeRightPin = 12;

int left = LOW;
int right = LOW;

//setup
Servo tilt;   //create servo object to control tilt servo
Servo swipe;  // create servo object to control swiping servo

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
    swipeLeft();
    delay(500);
  }
  delay(5000);
  for (int i = 0; i < 20; ++i) {
    swipeRight();
    delay(500);
  }
}

void runRF() {
  left = digitalRead(swipeLeftPin);
  right = digitalRead(swipeRightPin);
  if (left == HIGH && right == LOW) {
    swipeLeft();
    left = LOW;
    right = LOW;
  } else if (left == LOW && right == HIGH) {
    swipeRight();
    left = LOW;
    right = LOW;
  }
}