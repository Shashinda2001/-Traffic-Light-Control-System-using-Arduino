
// Pin definitions for pedestrian path
const int redPedestrianPin = 8;
const int greenPedestrianPin = 9;


// Pin definitions for vehicle path
const int redVehiclePin = 10;
const int yellowVehiclePin = 11;
const int greenVehiclePin = 12;

// Button pin and timing variables
const int buttonPin = 2;
const unsigned long buttonDebounceDelay = 50; // Debounce delay in milliseconds
const unsigned long vehicleGreenToYellowDelay = 2000; // Delay before changing vehicle light to yellow
const unsigned long yellowBlinkInterval = 1000; // Yellow blink interval in milliseconds
const unsigned long yellowBlinkDuration = 3000; // Total yellow blink duration in milliseconds
const unsigned long pedestrianCrossDuration = 5000; // Duration pedestrian light is green

// State variables
bool lastButtonState = LOW;
bool buttonState = LOW;
unsigned long lastDebounceTime = 0;
bool pedestrianGreenOn = false;
bool vehicleGreenOn = true;
unsigned long yellowBlinkStartTime = 0;
bool yellowBlinking = false;
unsigned long pedestrianCrossStartTime = 0;
void setup() {
  // put your setup code here, to run once:
   
}

void loop() {
  
 // Set all pins as output or input
  pinMode(redPedestrianPin, OUTPUT);
  pinMode(greenPedestrianPin, OUTPUT);
  pinMode(redVehiclePin, OUTPUT);
  pinMode(yellowVehiclePin, OUTPUT);
  pinMode(greenVehiclePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize LEDs
  initializeLights();
}

//
//Pedestrian Path-Red and Green lights. Initially,
//Red is ON. After the button is pressed, the Red turns 
//OFF and Green turns ON after 6 seconds. ,Vehicle Path-Red,
//Yellow, Green lights. Initially, Green is ON. After the button
//is pressed, Green turns to Yellow after 2 seconds, Yellow blinks
//for 3 seconds, then the pedestrian Green turns ON.
