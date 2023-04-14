//receive_RF.ino
//Program to control swipe and tilt servos using RF communication with the remote controller for the B.A.T.T. page turning subsystem
//Written by: Andrew Deering
//Trinity University, Engineering Science, Spring 2023

//Libraries
#include <PWMServo.h>           //Arduino servo library, will need to download from library manager
#include "VirtualWire.h"     //from: http://www.airspayce.com/mikem/arduino/VirtualWire/
#include "turnPage.h"        //page turning header file
#include "serialMovement.h"  //serial control of servos, useful for debugging


//      Variables
//contained in serialMovement.h
//int swipePos; //variable to store the swipe servo angle in degrees
//int tiltPos; //variable to store the tilt servo angle in degrees

//contained in turnPage.h
//Servo tilt; //create servo object to control tilt servo
//Servo swipe;  // create servo object to control swiping servo
//RGB LED PWM pins on the Arduino UNO
//const int ledRED = 11;
//const int ledGREEN = 10;
//const int ledBLUE = 9;

const int datain = 14;  //Data input pin connected to the RF receiver


void setup() {
  tilt.attach(5);      // attaches the servo on pin 5 to the tilt servo object
  swipe.attach(3);     //attaches the servo on pin 3 to the swipe servo object
  Serial.begin(9600);  //starting serial communication, use for debugging

  //configuring LED pins as output and turning it off
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);
   //LED color testing
  setColor(255, 0, 0); //red
  delay(500);
  setColor(0, 255, 0); //green
  delay(500);
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
  //runTests()

  //**FOR SERIAL BASED PAGE TURNER TESTING: UNCOMMENT THE NEXT LINE AND COMMENT OUT EVERYTHING ELSE IN THE LOOP**
  //serialMovement()

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
