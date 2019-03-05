// https://create.arduino.cc/editor/asg017/12c8ef32-3df8-41e1-9892-e65618494fe6/preview
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int16_t max_AcX,max_AcY,max_AcZ,max_Tmp,max_GyX,max_GyY,max_GyZ;
int16_t min_AcX,min_AcY,min_AcZ,min_Tmp,min_GyX,min_GyY,min_GyZ;


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
  /*
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  //*/
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
  
  Serial.print("AcX = "); Serial.print(min_AcX);Serial.print("_");Serial.print(max_AcX);
  Serial.print(" | AcY = "); Serial.print(min_AcY);Serial.print("_");Serial.print(max_AcY);
  Serial.print(" | AcZ = "); Serial.print(min_AcZ);Serial.print("_");Serial.print(max_AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(min_GyX);Serial.print("_");Serial.print(max_GyX);
  Serial.print(" | GyY = "); Serial.print(min_GyY);Serial.print("_");Serial.print(max_GyY);
  Serial.print(" | GyZ = "); Serial.println(min_GyZ);Serial.print("_");Serial.print(max_GyZ);
  
  delay(333);
}
