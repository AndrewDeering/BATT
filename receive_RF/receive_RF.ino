//receive_RF.ino
//Program to control swipe and tilt servos using RF communication with the remote controller for the B.A.T.T. page turning subsystem
//Written by: Andrew Deering
//Trinity University, Engineering Science, Spring 2023

//Libraries
#include "VirtualWire.h"     //from: http://www.airspayce.com/mikem/arduino/VirtualWire/

//      Variables
//RGB LED PWM pins on the Arduino UNO
const int ledRED = 11; 
const int ledGREEN = 10;
const int ledBLUE = 9;

const int swipeLeftPin = 3; //Digital pin connected to the arduino nano driving the servos
const int swipeRightPin = 2; //Digital pin connected to the arduino nano driving the servos
const int datain = 14;  //Data input pin connected to the RF receiver

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(ledRED, redValue);
  analogWrite(ledGREEN, greenValue);
  analogWrite(ledBLUE, blueValue);
}

void swipeLeft() {
  digitalWrite(swipeLeftPin, HIGH);
  digitalWrite(swipeRightPin, LOW);
  delay(50);
  digitalWrite(swipeLeftPin, LOW);
  delay(1000);
}

void swipeRight() {
  digitalWrite(swipeLeftPin, LOW);
  digitalWrite(swipeRightPin, HIGH);
  delay(50);
  digitalWrite(swipeRightPin, LOW);
  delay(1000);
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

void setup() {
  Serial.begin(9600);  //starting serial communication, use for debugging

  //configuring LED pins as output and turning it off
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);
  pinMode(swipeLeftPin, OUTPUT);
  pinMode(swipeRightPin, OUTPUT);

   //LED color testing
  setColor(255, 0, 0); //red
  delay(500);
  swipeRight();
  setColor(0, 255, 0); //green
  delay(500);
  swipeLeft();
  setColor(0, 0, 255); //blue
  delay(500);
  setColor(0,0,0);

  //RF Communication setup
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(datain);
  vw_setup(2000);
  vw_rx_start();
}

void loop() {
  //**FOR PAGE TURNER TESTING: UNCOMMENT THE NEXT LINE AND COMMENT OUT EVERYTHING ELSE IN THE LOOP**
  //runTests();

  //**FOR SERIAL BASED PAGE TURNER TESTING: UNCOMMENT THE NEXT LINE AND COMMENT OUT EVERYTHING ELSE IN THE LOOP**
  //serialMovement();

  //parsing RF message
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];      //Buffer containing the RF message
  uint8_t buflen = VW_MAX_MESSAGE_LEN;  //Message buffer length

  if (vw_get_message(buf, &buflen)) {
    //Serial.println(buf[0]);  //prints first buffer character to serial monitor, useful for debugging
    if (buf[0] == '0') {   // Number 1 means turn page forward
      //Serial.println("forward");  //prints first buffer character to serial monitor, useful for debugging
      setColor(0,255,0);
      swipeRight();        //turn page forward
    }
    if (buf[0] == '1') {  //Number 2 means turn page backward
      //Serial.println("backward");  //prints first buffer character to serial monitor, useful for debugging
      setColor(255,0,0);
      swipeLeft();        //turn page backward
    }
    if (buf[0] == '2') {  //Number 0 means no page turning
      setColor(0, 0, 0);  //turn off led
    }
  }
}
