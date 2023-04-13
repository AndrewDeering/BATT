#include "VirtualWire.h"
const int ledLeft = 2;
const int SWLeft = 7;
const int ledRight = 3;
const int SWRight = 8;
int timerDelay = 1000;
int signalDuration = 500;
int left = 0;
int right = 0;
char *data;
void setup() {
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(SWLeft, INPUT_PULLUP);
  pinMode(SWRight, INPUT_PULLUP);
  //Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(2000);
}

void loop() {
  /*data = "1";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  digitalWrite(ledLeft, HIGH);
  delay(2000);
  data = "0";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();
  digitalWrite(ledRight, LOW);
  delay(500);*/

  left = digitalRead(SWLeft);
  right = digitalRead(SWRight);
  if (left == HIGH && right == LOW) {  //turn page forward
    delay(timerDelay);
    //check if buttons are still in the correct configuration
    left = digitalRead(SWLeft);
    right = digitalRead(SWRight);
    if (left == HIGH && right == LOW) {
      data = "2";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();
      digitalWrite(ledLeft, LOW);
      digitalWrite(ledRight, HIGH);
      delay(signalDuration);
    }
  } else if (left == LOW && right == HIGH) {  //turn page backward
    delay(timerDelay);
    //check if buttons are still in the correct configuration
    left = digitalRead(SWLeft);
    right = digitalRead(SWRight);
    if (left == LOW && right == HIGH) {
      data = "1";
      vw_send((uint8_t *)data, strlen(data));
      vw_wait_tx();
      digitalWrite(ledLeft, HIGH);
      digitalWrite(ledRight, LOW);
      delay(signalDuration);
    }
  } else {  //do not turn page
    data = "0";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
  }
}