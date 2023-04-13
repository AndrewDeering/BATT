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
//int SW1 = 11; //Switch 1 attached to pin 12
//int SW2 = 12; //switch 2 attached to pin 11
//int LED = 2; //test led on pin 2
int DIP1 = A1;  //DIP configuration switch 1 attached to analog pin 1
int DIP2 = A2;  //DIP configuration switch 1 attached to analog pin 1
int mode1 = LOW;
int mode2 = LOW;

void setup() {
  tilt.attach(5);      // attaches the servo on pin 5 to the tilt servo object
  swipe.attach(3);     //attaches the servo on pin 4 to the swipe servo object
  Serial.begin(9600);  //setup serial communication for input

  pinMode(SW1, INPUT);  //Digital input from sw1 and sw2
  pinMode(SW2, INPUT);
  pinMode(DIP1, INPUT);  //Digital input from sw1 and sw2
  pinMode(DIP2, INPUT);
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);
  setColor(0,0,0);

  //test section to verify servos are working
  tiltPos = 90;
  swipePos = 90;
  writePos();  //contained in turn page, writes tiltPos and swipePos to the servos
  setColor(0,0,255);
  delay(500);
  swipePos = 10;
  writePos();  //contained in turn page, writes tiltPos and swipePos to the servos
  setColor(0,0,0);
  delay(500);
}

void loop() {  //Three operating modes for this program based on DIP switch
  /*
  mode1 = digitalRead(DIP1);
  mode2 = digitalRead(DIP2);
  if (mode1 == HIGH && mode2 == LOW) {  //Manual operation
    digitalWrite(testLED, LOW);
    while (digitalRead(DIP1) == HIGH && digitalRead(DIP2) == LOW) {
      runManual();  //Uses pushbutton inputs to turn the pages left and right
    }
  } else if (mode1 == HIGH && mode2 == HIGH) {
    while (digitalRead(DIP1) == HIGH && digitalRead(DIP2) == HIGH) {
      serialMovement();  //Uses serial monitor input to set the angle of each servo
    }
  } else if (mode1 == LOW && mode2 == HIGH) {
    runTests();  //Automatically runs the page turner prototype testing
  }
  digitalWrite(testLED, HIGH);
  delay(50);
  */
  //runManual();
  runTests();
  //serialMovement();
}