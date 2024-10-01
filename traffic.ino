
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

void loop() {
  // Read button state
  bool reading = digitalRead(buttonPin);

  // Handle button debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > buttonDebounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // Button press detected
      if (buttonState == LOW) {
        startSequence();
      }
    }
  }

  lastButtonState = reading;

  // Handle yellow light blinking
  if (yellowBlinking) {
    if (millis() - yellowBlinkStartTime < yellowBlinkDuration) {
      if ((millis() - yellowBlinkStartTime) % (2 * yellowBlinkInterval) < yellowBlinkInterval) {
        digitalWrite(yellowVehiclePin, HIGH); // Yellow light ON
      } else {
        digitalWrite(yellowVehiclePin, LOW); // Yellow light OFF
      }
    } else {
      stopSequence();
    }
  }
  
  // Handle pedestrian crossing duration
  if (pedestrianGreenOn && (millis() - pedestrianCrossStartTime > pedestrianCrossDuration)) {
    digitalWrite(greenPedestrianPin, LOW); // Turn off pedestrian green light
    digitalWrite(redPedestrianPin, HIGH); // Turn pedestrian red light back on
  }
}

void initializeLights() {
  // Set initial state
  digitalWrite(redPedestrianPin, HIGH); // Pedestrian red light ON
  digitalWrite(greenPedestrianPin, LOW); // Pedestrian green light OFF
  digitalWrite(redVehiclePin, LOW); // Vehicle red light OFF
  digitalWrite(yellowVehiclePin, LOW); // Vehicle yellow light OFF
  digitalWrite(greenVehiclePin, HIGH); // Vehicle green light ON
}

void startSequence() {
  // Start vehicle light change sequence
  delay(vehicleGreenToYellowDelay); // Wait 2 seconds before changing vehicle lights

  // Change vehicle green light to yellow
  digitalWrite(greenVehiclePin, LOW); // Vehicle green light OFF
  digitalWrite(yellowVehiclePin, HIGH); // Vehicle yellow light ON
  yellowBlinkStartTime = millis();
  yellowBlinking = true;

  // Change pedestrian lights
  digitalWrite(redPedestrianPin, LOW); // Pedestrian red light OFF
  digitalWrite(greenPedestrianPin, HIGH); // Pedestrian green light ON
  pedestrianGreenOn = true;
  pedestrianCrossStartTime = millis(); // Start the pedestrian crossing timer
}

void stopSequence() {
  // Turn off yellow light and restore vehicle lights
  digitalWrite(yellowVehiclePin, LOW); // Vehicle yellow light OFF
  digitalWrite(redVehiclePin, HIGH); // Vehicle red light ON
  yellowBlinking = false;

  // After yellow blinking, turn off pedestrian green light and turn on pedestrian red light
  digitalWrite(greenPedestrianPin, LOW); // Pedestrian green light OFF
  digitalWrite(redPedestrianPin, HIGH); // Pedestrian red light ON

  // Ensure vehicle green light is restored to initial state
  delay(vehicleGreenToYellowDelay); // Ensure vehicle red light is ON for some time
  digitalWrite(greenVehiclePin, HIGH); // Vehicle green light ON

  // Reset system to initial state
  initializeLights();
}

//
//Pedestrian Path-Red and Green lights. Initially,
//Red is ON. After the button is pressed, the Red turns 
//OFF and Green turns ON after 6 seconds. ,Vehicle Path-Red,
//Yellow, Green lights. Initially, Green is ON. After the button
//is pressed, Green turns to Yellow after 2 seconds, Yellow blinks
//for 3 seconds, then the pedestrian Green turns ON.
