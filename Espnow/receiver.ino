//Receiver
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include "user_interface.h"
}

uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
void initVariant() {
  wifi_set_macaddr(STATION_IF, &mac[0]);
}

byte cnt=0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\r\nESP_Now MASTER CONTROLLER\r\n");
  delay(1000);

 esp_now_init();
 esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
      //Serial.printf("Got Something length =\t%i", len);
      //Serial.println();
      //String s = String(((char*)data));
      //Serial.println(s);


//----working------//
      
     String s;
      for (int i=0; i < len; i++) s += char(data[i]);
      Serial.println(s);





      
  });
}

void loop()
{
  
}

