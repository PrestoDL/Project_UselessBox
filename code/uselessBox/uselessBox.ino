#include <Servo.h>
#include <LowPower.h>

Servo lidServo;
Servo armServo;

// macro
const int LID_CLOSED = 85; 
const int LID_OPEN = 35;
const int ARM_REST = 180;
const int ARM_PUSH = 65;

// pinout
const int button = 2;
const int lid = 10;
const int arm = 11;
const int led = 13;

void wakeUp() {
  // interrupt
}

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(lid, OUTPUT);
  pinMode(arm, OUTPUT);
  pinMode(led, OUTPUT);

  pinMode(3, OUTPUT); // alternate GND
  digitalWrite(3, LOW); // im lazy that i didn't make circuit firmly
  
  digitalWrite(led, HIGH);

  lidServo.attach(lid);
  armServo.attach(arm, 544, 2550);
  lidServo.write(LID_CLOSED);
  armServo.write(ARM_REST);
  delay(300);
  
  lidServo.detach();
  armServo.detach();
}

void loop() {
  digitalWrite(led, HIGH);
  
  // Wake and Check switch
  if (digitalRead(button) == LOW) { // button activated
    
    lidServo.attach(lid);
    armServo.attach(arm, 544, 2550);

    lidServo.write(LID_OPEN);
    delay(500);

    armServo.write(ARM_PUSH);
    delay(600);
    while(digitalRead(button) == LOW) { // button still activate
      delay(80);
    }

    armServo.write(ARM_REST);
    delay(500);

    lidServo.write(LID_CLOSED);
    delay(300);

    // Detach servo
    lidServo.detach();
    armServo.detach();
  }

  // Enter Sleep Mode
  digitalWrite(led, LOW);

  // Interrupt Attach
  attachInterrupt(digitalPinToInterrupt(button), wakeUp, LOW);
  
  // Deep Sleep Mode
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  // Interrupt Detach
  detachInterrupt(digitalPinToInterrupt(button)); 
}