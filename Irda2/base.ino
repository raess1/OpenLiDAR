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

#include <SoftwareSerial.h>
//Define pins for TX/RX
#define rxPin 12  // GPIO #D6 -> RX pin on IrDA2
#define txPin 14  // GPIO #D5 // -> TX pin on IrDA2

// set up a new serial port
SoftwareSerial inputPort =  SoftwareSerial(rxPin, txPin, false);

void setup()  {
  // set the data rate for the SoftwareSerial port
  inputPort.begin(115200);
  Serial.begin(115200);
  Serial.println("nStarting to listen...n");
  delay(200);
}

void loop() 
{
  if (inputPort.available())
  {
    Serial.print((char)inputPort.read());
  }
}
