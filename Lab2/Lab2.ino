#include "Wire.h" //This is a library that allows the program to communicate with I2C devices.

const int pinX = A0;
const int pinY = A1;
const int buzzerPin = 28;
const int buzzerFrequency = 1750;
char serial_In;
int X;
int Y;
char Serial_out;

const int MPU_ADDR=0x68; // I2C address of the MPU-6050. If AD0 pin is set to high, the I2C adress will be 0x69.

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data

char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  Serial.begin(9600); //A larger speed is used to speed up the transfer rate
  Serial.setTimeout(100000);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  // put your main code here, to run repeatedly:

  Wire.beginTransmission(MPU_ADDR);

  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR,6,true);
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  if(gyro_x>5000){
    Serial_out = 's';
    }
  if(gyro_x<-5000){
    Serial_out = 'w';
    
    }
  if(gyro_y>5000){
    Serial_out = 'd';

    }
  if(gyro_y<-5000){
    Serial_out = 'a';
    }


  serial_In = Serial.read();
  
  X = analogRead(pinX); // Read the X axis analog value
  Y = analogRead(pinY); // Read the Y axis analog value
  
  // Check for signal indicating if apple has been eaten, if it has then beep the buzzer
  if(serial_In == 'b'){
    tone(buzzerPin, buzzerFrequency);
    delay(100);
    noTone(buzzerPin);
  }
  
  // Check what direction joystick is pointing and send a signal to the serial port
  // UP
  if(Y < 300){
    Serial_out = 'w';
  }
  // DOWN
  if(Y > 700){
    Serial_out = 's';
  }
  // RIGHT
  if(X > 700){
    Serial_out = 'd';
  }
  // LEFT
  if(X < 300){
    Serial_out = 'a';
  }
      if(serial_In=='r'){
      Serial.write(Serial_out);
      }
  //if(Serial.read() == 'r'){
  //  digitalWrite(22,HIGH);
  //  }
  //delay(400);
}
