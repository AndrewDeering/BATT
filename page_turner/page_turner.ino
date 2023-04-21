//page_turner.ino
//Program to control swipe and tilt servos for the B.A.T.T. page turning subsystem
//Written by: Andrew Deering
//Trinity University, Engineering Science

//Libraries
#include <Servo.h>  //default arduino servo library

#include "turnPage.h"        //header file containing page turning logic
#include "serialMovement.h"  //header file containing logic for adjusting both servo angles with serial monitor input

//Variables
//contained in serialMovement.h
//int swipePos; //variable to store the swipe servo angle in degrees
//int tiltPos; //variable to store the tilt servo angle in degrees

//contained in turnPage.h
//Servo tilt; //create servo object to control tilt servo
//Servo swipe;  // create servo object to control swiping servo
//const int swipeLeftPin = 11;
//const int swipeRightPin = 12;

void setup() {
  tilt.attach(5);      // attaches the servo on pin 5 to the tilt servo object
  swipe.attach(3);     //attaches the servo on pin 4 to the swipe servo object
  Serial.begin(9600);  //setup serial communication for input

  pinMode(swipeLeftPin, INPUT);  //Digital input from sw1 and sw2
  pinMode(swipeRightPin, INPUT);

  //test section to verify servos are working
  tiltPos = 90;
  swipePos = 90;
  writePos();  //contained in turn page, writes tiltPos and swipePos to the servos
  delay(500);
  swipePos = 10;
  writePos();  //contained in turn page, writes tiltPos and swipePos to the servos
  delay(500);
}

void loop() {  //Three operating modes for this program
  runRF();
  //runTests();
  //serialMovement();
}