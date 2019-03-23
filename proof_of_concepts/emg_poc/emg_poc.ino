/*
  This snippet is to see how the EMG works with the Arduino.
  
  The ouput is connected to A3, and at first when we DIDNT connect the ardunio ground
  to the circuit ground, it acted like so:
  
  1. Reading was aroudn 1023, arm unlfex
  2. Arm flex, reading eventually go to 0
  3. Arm flex again, readings dont change, then go back to 1020 after a few seconds
  
  Whwen we DID connect the grounds together, the readings were all over the place (100-400
  when not flexing). Soooooo 🤷 
*/

const int EMG_PIN = A3; // Pin connected to voltage divider output

void setup() 
{
  Serial.begin(9600);
  pinMode(EMG_PIN, INPUT);
}

void loop() 
{
  int emgRead = analogRead(EMG_PIN);
  Serial.println("emg: " + String(emgRead));
  delay(250);
}
