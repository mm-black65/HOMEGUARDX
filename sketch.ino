#include <ESP32Servo.h>

/******** PIN DEFINITIONS ********/

// Sensors
#define THERMISTOR_PIN 34
#define LDR_PIN        35
#define PIR_PIN        27
#define DOOR_BUTTON    14
#define MODE_BUTTON    25

// Outputs
#define TEMP_LED       18
#define LIGHT_LED      23
#define INTRUDER_LED   5
#define DOOR_LED       12
#define BUZZER_PIN     19
#define NORMAL_LED     4
#define SECURITY_LED   2
#define SERVO_PIN      13

/******** CONFIGURATION & THRESHOLDS ********/
const int tempThreshold   = 1500;
const int darkThreshold   = 1800; // Turn ON light
const int brightThreshold = 2200; // Turn OFF light 

Servo doorServo;
bool securityMode = false;

// Timing Variables 
unsigned long lastTempBuzz = 0;
unsigned long lastIntruderBuzz = 0;
unsigned long doorTimer = 0;
const unsigned long tempBuzzInterval = 200;
const unsigned long intruderBuzzInterval = 150;

// State Tracking
bool doorIsOpening = false;

void setup() {
  Serial.begin(115200);
  

  // Initialize Pins
 
 int outputs[] = {TEMP_LED, LIGHT_LED, INTRUDER_LED, DOOR_LED, BUZZER_PIN,      
   NORMAL_LED, SECURITY_LED};
  for(int pin : outputs) pinMode(pin, OUTPUT);

  pinMode(PIR_PIN, INPUT);
  pinMode(DOOR_BUTTON, INPUT_PULLUP);
  pinMode(MODE_BUTTON, INPUT_PULLUP);

  // Servo Setup
  ESP32PWM::allocateTimer(0);
  doorServo.setPeriodHertz(50);
  doorServo.attach(SERVO_PIN, 500, 2400);
  doorServo.write(0); 

 
  digitalWrite(NORMAL_LED, HIGH);
  Serial.println("System Ready. Mode: NORMAL");
}

void loop() {
  handleModeToggle();
  handleTemperature();
  handleLightSensing();
  handleIntrusion();
  handleDoor();
  
  
  delay(10); 
}

/******** MODULE 1: MODE TOGGLE  ********/
void handleModeToggle() {
  static bool lastBtn = HIGH;
  bool currentBtn = digitalRead(MODE_BUTTON);

  if (lastBtn == HIGH && currentBtn == LOW) {
    securityMode = !securityMode;
    digitalWrite(NORMAL_LED, !securityMode);
    digitalWrite(SECURITY_LED, securityMode);
    Serial.print("Mode Switched: ");
    Serial.println(securityMode ? "SECURITY" : "NORMAL");
    delay(50); 
  }
  lastBtn = currentBtn;
}

/******** MODULE 2: TEMPERATURE ********/
void handleTemperature() {
  int tempValue = analogRead(THERMISTOR_PIN);
  if (tempValue < tempThreshold) {
    digitalWrite(TEMP_LED, HIGH);
    if (millis() - lastTempBuzz > tempBuzzInterval) {
      tone(BUZZER_PIN, 600, 100);
      lastTempBuzz = millis();
    }
  } else {
    digitalWrite(TEMP_LED, LOW);
  }
}

/******** MODULE 3: LIGHT ********/
void handleLightSensing() {
  static int smoothedLight = 2000;
  int currentRead = analogRead(LDR_PIN);
  
  
  smoothedLight = (smoothedLight * 0.9) + (currentRead * 0.1);

  if (smoothedLight < darkThreshold) {
    digitalWrite(LIGHT_LED, HIGH);
  } else if (smoothedLight > brightThreshold) {
    digitalWrite(LIGHT_LED, LOW);
  }
}

/******** MODULE 4: INTRUSION ********/
void handleIntrusion() {
  if (digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(INTRUDER_LED, HIGH);
    if (millis() - lastIntruderBuzz > intruderBuzzInterval) {
      // Higher pitch if in security mode
      tone(BUZZER_PIN, securityMode ? 1200 : 800, 80);
      lastIntruderBuzz = millis();
    }
  } else {
    digitalWrite(INTRUDER_LED, LOW);
    // Only stop tone if temperature isn't also triggering it
    if (analogRead(THERMISTOR_PIN) >= tempThreshold) noTone(BUZZER_PIN);
  }
}

/******** MODULE 5: DOOR  ********/
void handleDoor() {
  // Trigger door if button pressed and not already moving
  if (digitalRead(DOOR_BUTTON) == LOW && !doorIsOpening) {
    doorIsOpening = true;
    doorTimer = millis();
    doorServo.write(90);
    digitalWrite(DOOR_LED, HIGH);
    Serial.println("Door Opened");
  }

  // Auto-close door after 3 seconds
  if (doorIsOpening && (millis() - doorTimer > 3000)) {
    doorServo.write(0);
    digitalWrite(DOOR_LED, LOW);
    doorIsOpening = false;
    Serial.println("Door Closed");
  }
}
