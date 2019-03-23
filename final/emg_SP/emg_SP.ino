#include <Servo.h>
#define baseServoPin 3

Servo baseServo;

const int numReadings=15; //size of readings array
int readings[numReadings];  //readings from the analog input
int readIndex=0; //index of current reading
int total=0; //running total
int average=0; //average

int EMG=A3; //signal 
int mapping;
int counter = 0;
int isOn = 0; 


void setup() {
  // put your setup code here, to run once:
  baseServo.attach(baseServoPin);
  baseServo.write(150);
  Serial.begin(9600);
  //initialize:
  for (int thisReading=0; thisReading < numReadings; thisReading++) {
    readings[thisReading]=0;
  }
}

void loop() {
  
  // put your main code here, to run repeatedly:
total=total-readings[readIndex]; //subtract last reading
readings[readIndex]=analogRead(EMG); //read EMG
total=total+readings[readIndex]; //add that reading to total
readIndex=readIndex+1; //advance to next position

//for end of array:
if (readIndex >= numReadings) {
  readIndex=0;
}
average=total/numReadings; //calculate average
Serial.println(average);

//mapping = map(average, 240, 0, 180, 180);
 
  if (average >= 230){
    isOn = 1; 
  }
  if (isOn == 1){
      baseServo.write(100);
      isOn++;
  }
  if (isOn == 2){
      baseServo.write(145);
      isOn = 0;
  }
  
delay(1); //stability
//baseServo.write(average);
}
