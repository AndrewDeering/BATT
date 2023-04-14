#include "VirtualWire.h"
const int SWLeft = 10;   //pin for the left switch (forward)
const int SWRight = 12;  //pin for the right switch (backward)
const int dataOut = 8;   //pin to send information to the RF transmitter
//RGB LED pins
const int ledBLUE = 4;
const int ledGREEN = 5;
const int ledRED = 6;
const int delayTime = 1000;  //Required duration in ms to hold inputs before sending signals
//Variables to store the switch input values
int left = 0;
int right = 0;

char *data;  //variable to store the message sent to the RF receiver. 2 = no page turn; 0 = turn page forward; 1 = turn page backward

void setColor(int red, int green, int blue) {
  analogWrite(ledRED, red);
  analogWrite(ledBLUE, blue);
  analogWrite(ledGREEN, green);
}

void setup() {
  //configuring the LED pins as outputs
  pinMode(ledRED, OUTPUT);
  pinMode(ledGREEN, OUTPUT);
  pinMode(ledBLUE, OUTPUT);

  //Input switches operating in active low
  pinMode(SWLeft, INPUT_PULLUP);
  pinMode(SWRight, INPUT_PULLUP);
  //LED color testing
  setColor(255, 0, 0); //red
  delay(500);
  setColor(0, 255, 0); //green
  delay(500);
  setColor(0, 0, 255); //blue
  delay(500);
  setColor(0,0,0);

  Serial.begin(9600);  //used to start serial communication, can use for debugging

  //RF communication setup
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(dataOut);
  vw_setup(2000);
}

void loop() {
  //Reading the input switches
  left = digitalRead(SWLeft);
  right = digitalRead(SWRight);
  if (left == LOW && right == HIGH) {  //Page forward input received
    delay(delayTime);
    left = digitalRead(SWLeft);
    right = digitalRead(SWRight);
    if (left == LOW && right == HIGH) {  //Checking to see if input was held for the full duration
      data = "0";
      Serial.println(data);
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();
      setColor(0, 255, 0);  //set LED green
      delay(1000);
      setColor(0,0,0);
      delay(3000);
    }
  } else if (left == HIGH && right == LOW) {  //Page backward input received
    delay(delayTime);
    left = digitalRead(SWLeft);
    right = digitalRead(SWRight);
    if (left == HIGH && right == LOW) {  //Checking to see if input was held for the full duration
      data = "1";
      Serial.println(data);
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();
      setColor(255, 0, 0);  //set LED red
      delay(1000);
      setColor(0,0,0);
      delay(3000);
    }
  } else {  //do not turn page
    data = "2";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
  }
  setColor(0, 0, 0);  //turn LED off
}
