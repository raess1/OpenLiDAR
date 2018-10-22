/*
OpenLidar 
Link: https://hackaday.io/project/159994-openlidar
Hardware: 
Nodemcu: https://www.kjell.com/se/sortiment/el-verktyg/arduino/utvecklingskort/nodemcu-utvecklingskort-p87949
LidarLiteV3: https://www.sparkfun.com/products/14032
IrDA2 click board: https://www.mikroe.com/irda2-click
Wireless power coils:
Nodemcu pinout: https://iotbytes.wordpress.com/nodemcu-pinout/
 */
#include <Wire.h>
#include <LIDARLite.h>
LIDARLite myLidarLite;
#include <SoftwareSerial.h>

#define rxPin 12  // GPIO #D6 -> RX pin on IrDA2
#define txPin 14  // GPIO #D5 // -> TX pin on IrDA2

SoftwareSerial displayPort(rxPin, txPin); // Rx, Tx

void setup()  {

  // set the data rate for the SoftwareSerial port
  Serial.begin(115200);
  displayPort.begin(115200);
  delay(200);
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop() 
{ 
  Serial.println(myLidarLite.distance());
  {
    Serial.println(myLidarLite.distance(false));
  }
  displayPort.println(myLidarLite.distance(false));
  delay(10);  
}
