// --- LIBRARIES --- //
#include <Servo.h>

// --- GLOBAL VARIABLES --- //
// human switch
const int humanPin = A0;
const int humanPin2 = A1;
const int numReadings = 10;
int total = 0;
int total2 = 0;
// servos
const int servoPin1 = 3;
const int servoPin2 = 5;
Servo myservo1;
Servo myservo2;
int servoPosition1;
int servoPosition2;
int pos = 90;
bool servoPosIncrease = true;
// test button
const int buttonPin = 2;
bool isAvailableButton = true;

// --- SETUP --- //
void setup() {
  // open serial monitor
  Serial.begin(9600);
  // attach servo objects to the servo pins
  myservo1.attach(servoPin1);  
  myservo2.attach(servoPin2);
  myservo1.write(90);
  myservo2.write(90);
  // set up button as output
  pinMode(buttonPin, INPUT);
}


// --- MAIN LOOP --- //
void loop() {
  // --- Human Switch --- //
  for (int i=0; i<numReadings; i++) {
    int touchAmount = analogRead(humanPin);
    int touchAmount2 = analogRead(humanPin2);
    delay(1);
    total+=touchAmount;
    total2+=touchAmount2;
  }

  int averageTouchAmount = total/numReadings;
  int averageTouchAmount2 = total2/numReadings;
  total = 0; // reset
  total2 = 0;

  // map the reading on a scale of 0-100
  Serial.print("sensor 1: ");
  Serial.print(averageTouchAmount);

  Serial.print(" sensor 2: ");
  Serial.println(averageTouchAmount2);

  // --- Servos --- //
  if (averageTouchAmount > 0 && averageTouchAmount2 > 0) {
    if (servoPosIncrease == true) {
      if (pos < 125) {
        pos += 1;
        myservo1.write(pos);
        myservo2.write(pos);
//        Serial.print("increasing: ");
//        Serial.println(pos);
        delay(15);  
      } else {
        servoPosIncrease = false;
      }
    } else {
      if (pos > 65) {
        pos -= 1;
        myservo1.write(pos);
        myservo2.write(pos);
//        Serial.print("decreasing: ");
//        Serial.println(pos);
        delay(15);  
      } else {
        servoPosIncrease = true;
      }
    }
  }

//  if (servoPosIncrease == true) {
//    if (pos > 110) {
//      servoPosIncrease = false;
//    }
//  } else {
//    if (pos < 70) {
//      servoPosIncrease = true;
//    }
//  }

  Serial.println(pos);
  
//  delay(400);
}
