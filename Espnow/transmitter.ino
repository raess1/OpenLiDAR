//Transmiter
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

extern "C" {
  #include <espnow.h>
}

#define WIFI_CHANNEL 1

//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteMac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
const byte dataLength=7;
byte cnt=0;
byte rcvData[dataLength];
byte result;

void setup()
{
  Wire.begin(D4, D1);
  Serial.begin(115200);
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.print("\r\n\r\nDevice MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Controller.");
  esp_now_init();
  delay(10);
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0);

}  

void loop()
{
  for(cnt=0; cnt<dataLength; cnt++)
  {
    rcvData[cnt]++;
  }

Serial.println(myLidarLite.distance());
// Take 99 measurements without receiver bias correction and print to serial terminal
  for(int i = 0; i < 99; i++)
  {
    //Serial.println(myLidarLite.distance(false));
  }

  //----working-----//

      uint16_t dis = myLidarLite.distance();
      //Serial.println(dis); //debug
      String data;
      data = dis;
      const byte dataLength=7;
      byte rcvData[dataLength];
      itoa(dis,(char*)rcvData,10);
      result = esp_now_send(remoteMac, rcvData, dataLength);




      
      //----debugZ------//
      //char test[] = "hello";
      //result = esp_now_send(remoteMac, ((u8*)test), strlen(test));
      //result = esp_now_send(remoteMac, ((u8*)data.c_str()), data.length());
      //Serial.println(data);
      delay(0);
      
     
}

