/*
OpenLidar 
Link: https://hackaday.io/project/159994-openlidar
Hardware: 
Nodemcu: https://www.kjell.com/se/sortiment/el-verktyg/arduino/utvecklingskort/nodemcu-utvecklingskort-p87949
LidarLiteV3: https://www.sparkfun.com/products/14032
IrDA2 click board: https://www.mikroe.com/irda2-click
Wireless power coils:
Nodemcu pinout: https://iotbytes.wordpress.com/nodemcu-pinout/

Lidarlite V3 Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND

 */
#include <Wire.h>
#include <LIDARLite.h>
#include <SoftwareSerial.h>
LIDARLite myLidarLite;


#define rxPin 12  // GPIO #D6 -> RX pin on IrDA2
#define txPin 14  // GPIO #D5 // -> TX pin on IrDA2

#define sda_pin 5  // GPIO #D1 -> SDA
#define scl_pin 4  // GPIO #D2 // -> SCL

SoftwareSerial displayPort(rxPin, txPin); // Rx, Tx

void setup()  {

  // set the data rate for the SoftwareSerial port
  Wire.begin(sda_pin,scl_pin);
  Serial.begin(115200);
  displayPort.begin(115200);
  delay(200);
  // alternate configurations can be found here: https://github.com/garmin/LIDARLite_Arduino_Library/blob/master/examples/v3/GetDistanceI2c/GetDistanceI2c.ino
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop() 
{ 
  Serial.println(myLidarLite.distance());
  {
    // For debug data
    Serial.println(myLidarLite.distance(false));
  }
  displayPort.println(myLidarLite.distance(false));
  delay(10);  
}
