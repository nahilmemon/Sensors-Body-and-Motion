/*
  This code reads the values from six FSRs. Based off of these readings, the desired volumes
  and speeds for six different audio clips are mapped. These volumes and speeds are then sent
  through serial communication to Isadora, where six different audio clips are played with
  various volumes and speeds accordingly. 
*/
// ----- GLOBAL VARIABLES  ----- //
// store the pins that the FSRs are connected to
const int fsrPin1 = A0;
const int fsrPin2 = A1;
const int fsrPin3 = A2;
const int fsrPin4 = A3;
const int fsrPin5 = A4;
const int fsrPin6 = A5;
// store the readings of the FSRs
float fsrValue1;
float fsrValue2;
float fsrValue3;
float fsrValue4;
float fsrValue5;
float fsrValue6;
// store the volume output by mapping the fsr readings to the desired volume
float volume1;
float volume2;
float volume3;
float volume4;
float volume5;
float volume6;
// store the speed output by mapping the fsr readings to the desired speed
float speed1;
float speed2;
float speed3;
float speed4;
float speed5;
float speed6;

// ----- SETUP  ----- //
void setup() {
  // begin serial monitor
  Serial.begin(9600);
}

// ----- MAIN LOOP  ----- //
void loop() {
  // --- Read the FSRs  --- //
  fsrValue1 = analogRead(fsrPin1);
  fsrValue2 = analogRead(fsrPin2);
  fsrValue3 = analogRead(fsrPin3);
  fsrValue4 = analogRead(fsrPin4);
  fsrValue5 = analogRead(fsrPin5);
  fsrValue6 = analogRead(fsrPin6);

  // --- Map the FSRs to get Volume Outputs --- //
  // the default: if the sensor isn't in use,
  // then the volume is maxed out
  // if the sensor is being used, the volume decreases
  // but it never turns off
  volume1 = map(fsrValue1, 0, 930, 80, 20); // pen clicking
  volume1 = constrain(volume1, 20, 80);
  // note: can't map values to get floats, so I multiplied
  // the desired range by 1000, mapped it, then divided the
  // result by 1000 to get a float result
  volume2 = map(fsrValue2, 0, 930, 8000, 2000); // screaming
  volume2 = volume2/1000;
  volume2 = constrain(volume2, 2, 8);
  volume3 = map(fsrValue3, 0, 930, 40, 10); // blinds rattling
  volume3 = constrain(volume3, 10, 40);
  volume4 = map(fsrValue4, 0, 930, 100, 25); // clock ticking (low audio)
  volume4 = constrain(volume4, 25, 100);
  volume5 = map(fsrValue5, 0, 930, 80, 20); // fingernails on chalkboard
  volume5 = constrain(volume5, 20, 80);
  volume6 = map(fsrValue6, 0, 930, 40, 10); // crickets
  volume6 = constrain(volume6, 10, 40);

  // --- Map the FSRs to get Speed Outputs  --- //
  // the default: if the sensor isn't in use, 
  // then the speed is normal (1)
  // if the sensor is being used, the speed increases (up to 3)
  speed1 = map(fsrValue1, 0, 930, 100, 300);
  speed1 = speed1/100;
  speed1 = constrain(speed1, 1, 3);
  speed2 = map(fsrValue2, 0, 930, 100, 300);
  speed2 = speed2/100;
  speed2 = constrain(speed2, 1, 3);
  speed3 = map(fsrValue3, 0, 930, 100, 300);
  speed3 = speed3/100;
  speed3 = constrain(speed3, 1, 3);
  speed4 = map(fsrValue4, 0, 930, 100, 300);
  speed4 = speed4/100;
  speed4 = constrain(speed4, 1, 3);
  speed5 = map(fsrValue5, 0, 930, 100, 300);
  speed5 = speed5/100;
  speed5 = constrain(speed5, 1, 3);
  speed6 = map(fsrValue6, 0, 930, 100, 300);
  speed6 = speed6/100;
  speed6 = constrain(speed6, 1, 3);

  // --- Send information to isadora  --- //
  // --- Volume --- //
  sendToIsadora(1, volume1);
  sendToIsadora(2, volume2);
  sendToIsadora(3, volume3);
  sendToIsadora(4, volume4);
  sendToIsadora(5, volume5);
  sendToIsadora(6, volume6);
  // --- Speed --- //
  sendToIsadora(7, speed1);
  sendToIsadora(8, speed2);
  sendToIsadora(9, speed3);
  sendToIsadora(10, speed4);
  sendToIsadora(11, speed5);
  sendToIsadora(12, speed6);
  delay(250);
}

// ----- SEND DATA TO ISADORA  ----- //
void sendToIsadora(int route, float value) {
  // variable index (if you have 12 variables to send, 
  // this helps to organize the information separately 
  // when it gets to isadora 
  Serial.print(route); 
  Serial.print("|");
  // value of the variable whose info you are sending
  Serial.print(value);
  Serial.print(" ");    
}
