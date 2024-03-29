/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
//for the robotic arm implementation
#include <Servo.h>
#define elbowServoPin 6
#define shoulderServoPin 5

Servo elbowServo;
Servo shoulderServo;

const int FLEX_PIN = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 330.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 12000.0; // resistance when straight
const float BEND_RESISTANCE = 50000.0; // resistance at 90 deg

void setup() 
{
  elbowServo.attach(elbowServoPin);
  shoulderServo.attach(shoulderServoPin);
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(FLEX_PIN2, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  int flexADC2 = analogRead(FLEX_PIN2);
  float flexV = flexADC * VCC / 1023.0;
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);

  Serial.println("Resistance: " + String(flexR) + " ohms");
  Serial.println("Resistance: " + String(flexR2) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   50, 100.0);
                   
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   50, 100.0);
  
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
  Serial.println("Bend: " + String(angle2) + " degrees");
  Serial.println();
  elbowServo.write(angle);
  shoulderServo.write(angle2);

  //delay(500);
}
