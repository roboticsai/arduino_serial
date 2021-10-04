#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is

String data_received = "";
String data = "";
int offset =20;// set the correction offset value
unsigned long prev_time;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address
}

void loop() {
    while (Serial.available() > 0) {
      char incomingByte = Serial.read();
      data_received += incomingByte;
      if (mpu.update()) {
        unsigned long curr_time = millis();
        double dt = (prev_time - curr_time)/1000.0;
        prev_time = curr_time;
        data.concat(String(dt,3));  
        data.concat(",");
        data.concat(String(mpu.getQuaternionX(),3));  
        data.concat(",");
        data.concat(String(mpu.getQuaternionY(),3));  
        data.concat(",");
        data.concat(String(mpu.getQuaternionZ(),3));  
        data.concat(",");
        data.concat(String(mpu.getQuaternionW(),3));  
        data.concat(",");
        data.concat(String(mpu.getAccX(),3));  
        data.concat(",");
        data.concat(String(mpu.getAccY(),3));  
        data.concat(",");
        data.concat(String(mpu.getAccZ(),3));  
        data.concat(",");
        data.concat(String(mpu.getMagX(),3));  
        data.concat(",");
        data.concat(String(mpu.getMagY(),3));  
        data.concat(",");
        data.concat(String(mpu.getMagZ(),3));  
        data.concat(",");
        data.concat(String(mpu.getTemperature(),3));  
        data.concat(",");
        int volt = analogRead(A0); // read the input
        double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
          
        voltage /=100;// divide by 100 to get the decimal values
        data.concat(String(voltage,3));
        data.concat("\n");
        for (int i = 0; i < data.length(); i++) {
          Serial.write(data[i]);
        }
        data = "";
    }
  }
}
