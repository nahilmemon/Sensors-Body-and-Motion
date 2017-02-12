
/*  This is a modified version of the Pulse Sensor Amped 1.5 sketch created by 
    Joel Murphy and Yury Gitman   http://www.pulsesensor.com
    This code determines the beats per minute of a person, and sends this 
    information to be ready to be parsed by Isadora
 ----------------------       ----------------------  ----------------------
*/

#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

//  Variables
int pulsePin = A0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int pulseThreshold = 85;          // used to determine when to switch videos

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// SET THE SERIAL OUTPUT TYPE TO YOUR NEEDS
// PROCESSING_VISUALIZER works with Pulse Sensor Processing Visualizer
//      https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer
// SERIAL_PLOTTER outputs sensor data for viewing with the Arduino Serial Plotter
//      run the Serial Plotter at 115200 baud: Tools/Serial Plotter or Command+L
static int outputType = SERIAL_PLOTTER;


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);             // we agree to talk fast! 115200
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);
}


//  Where the Magic Happens
void loop(){

    serialOutput() ;

  // send the BPM to isadora
  // fast heartbeat
  if (BPM > pulseThreshold) {
    sendToIsadora(1, 0);  // show video 1 (the hamster)
    int mappedAmount = map(BPM, 125, pulseThreshold, 0, 20); // the faster the heartrate, the clearer the video (lesser the size of the gaussian blur effect)
    int constrainedAmount = constrain(mappedAmount, 0, 20);
    sendToIsadora(2, constrainedAmount);
  } else {                  // slow heart beat
    sendToIsadora(1, 100);  // show video 2 (the sea turtles)
    int mappedAmount = map(BPM, pulseThreshold, 65, 20, 0); // the slower the heartrate, the clearer the video (lesser the size of the gaussian blur effect)
    int constrainedAmount = constrain(mappedAmount, 0, 20);
    sendToIsadora(2, constrainedAmount);
  }

  delay(20);
}

// send information through serial communication to Isadora
void sendToIsadora(int route, int value) {
  Serial.print(route);
  Serial.print("|");
  Serial.print(value);
  Serial.print(" ");    
}
