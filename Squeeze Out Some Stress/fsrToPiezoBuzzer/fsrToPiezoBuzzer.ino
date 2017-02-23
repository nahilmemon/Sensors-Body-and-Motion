/*
  This code reads the values from an FSR. Based off of this, the frequency of the piezo 
  buzzer's tone changes. The harder you press, the higher the frequency, until you can't 
  really hear it anymore.
*/

// ----- GLOBAL VARIABLES  ----- //
const int tonePin = 8; // pin that the piezo buzzer is connected to
const int duration = 100; // duration of the beeping of the piezo buzzer
const int fsrPin01 = A0; // pin that the FSR is connected to

int fsrValue01; // to store the reading taken from the FSR

// ----- SETUP  ----- //
void setup() {
  // begin serial monitor
  Serial.begin(9600);
}

// ----- MAIN LOOP  ----- //
void loop() {
  // read the FSR and map it to the desired frequency range
  fsrValue01 = analogRead(fsrPin01); 
  // the mapping is from 0-900 because its readings are logarithmic and 
  // saturate at a certain point
  int mappedFSRValue01 = map(fsrValue01, 0, 900, 0, 20000); 
  int constrainedFSRValue01 = constrain(mappedFSRValue01, 0, 20000);

  // depict the FSR readings and frequencies in the serial monitor
  Serial.print("fsr 01: ");
  Serial.print(fsrValue01);
  Serial.print(" freq: ");
  Serial.println(constrainedFSRValue01);

  // make the piezo buzz
  tone(tonePin, constrainedFSRValue01, duration);

  // to make a beeping effect
  delay(duration*2);
}
