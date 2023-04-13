//serialMovement.h
//Program to control swipe and tilt servos for the B.A.T.T. page turning subsystem with pushbuttonb inputs
//Written by: Andrew Deering
//Trinity University, Engineering Science

//Libraries

//Variables
int swipePos;  //variable to store the swipe servo angle in degrees
int tiltPos;   //variable to store the tilt servo angle in degrees

void writePos() {  //writes tiltPos and swipePos to the servos
  tilt.write(tiltPos);
  swipe.write(swipePos);
  delay(100);
}

void serialMovement() { //Uses serial monitor input to set the angle of each servo
  Serial.print("loop tilt angle: ");
  Serial.println(tiltPos);
  writePos();
  Serial.println("Tilt(1) or Swipe(2) servo?");
  while (Serial.available() == 0) {
    writePos();
  }
  int type = Serial.parseInt();
  Serial.read();
  switch (type) {
    case 1:
      Serial.println("Enter tilt angle (0-180): ");
      while (Serial.available() == 0) {
        writePos();
      }
      tiltPos = Serial.parseInt();
      Serial.read();
      Serial.print("tilt angle: ");
      Serial.println(tiltPos);
      break;
    case 2:
      Serial.println("Enter swipe angle (0-180): ");
      while (Serial.available() == 0) {
        writePos();
      }
      swipePos = Serial.parseInt();
      Serial.read();
      break;
    default:
      Serial.println("Please enter a valid argument");
      break;
  }
}