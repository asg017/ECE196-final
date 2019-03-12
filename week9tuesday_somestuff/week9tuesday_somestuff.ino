#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int16_t max_AcX,max_AcY,max_AcZ,max_Tmp,max_GyX,max_GyY,max_GyZ;
int16_t min_AcX,min_AcY,min_AcZ,min_Tmp,min_GyX,min_GyY,min_GyZ;

const int FLEX_PIN = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1; // Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg


void setup(){
  max_AcX = -200000;
max_AcY= -200000;
max_AcZ= -200000;
max_Tmp = -200000;
max_GyX = -200000;
max_GyY= -200000;
max_GyZ= -200000;

min_AcX = 200000;
min_AcY= 200000;
min_AcZ= 200000;
min_Tmp =200000;
min_GyX = 200000;
min_GyY= 200000;
min_GyZ= 200000;
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  
  Serial.begin(9600);
  pinMode(FLEX_PIN2, INPUT);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //Serial.print("AcX = "); Serial.print(AcX);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.print(GyZ);
  
  //*/
  Serial.println();
  if(AcX > max_AcX)
    max_AcX = AcX;
  if(AcY > max_AcY)
    max_AcY = AcY;
  if(AcZ > max_AcZ)
    max_AcZ = AcZ;
  if(Tmp > max_Tmp)
    max_Tmp = Tmp;
  if(GyX > max_GyX)
    max_GyX = GyX;
  if(GyY > max_GyY)
    max_GyY = GyY;
  if(GyZ > max_GyZ)
    max_GyZ = GyZ;

if(AcX < min_AcX)
    min_AcX = AcX;
  if(AcY < min_AcY)
    min_AcY = AcY;
  if(AcZ < max_AcZ)
    min_AcZ = AcZ;
  if(Tmp < max_Tmp)
    min_Tmp = Tmp;
  if(GyX < max_GyX)
    min_GyX = GyX;
  if(GyY < max_GyY)
    min_GyY = GyY;
  if(GyZ < max_GyZ)
    min_GyZ = GyZ;
  
  
  /*
  Serial.print("AcX = "); Serial.print(min_AcX);Serial.print("_");Serial.print(max_AcX);
  Serial.print(" | AcY = "); Serial.print(min_AcY);Serial.print("_");Serial.print(max_AcY);
  Serial.print(" | AcZ = "); Serial.print(min_AcZ);Serial.print("_");Serial.print(max_AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(min_GyX);Serial.print("_");Serial.print(max_GyX);
  Serial.print(" | GyY = "); Serial.print(min_GyY);Serial.print("_");Serial.print(max_GyY);
  Serial.print(" | GyZ = "); Serial.print(min_GyZ);Serial.print("_");Serial.println(max_GyZ);
  //*/
  
  /*
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  int flexADC2 = analogRead(FLEX_PIN2);
  Serial.print("flexADC: ");
  Serial.print(flexADC);
  Serial.print("flexADC2: ");
  Serial.print(flexADC2);
  Serial.println();
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  //Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  //Serial.println("Bend: " + String(angle) + " degrees");
  //Serial.println();
  **/
  delay(333);
}
