/**

 */
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include "user_interface.h"
}

/* Set a private Mac Address
 *  http://serverfault.com/questions/40712/what-range-of-mac-addresses-can-i-safely-use-for-my-virtual-machines
 * Note: the point of setting a specific MAC is so you can replace this Gateway ESP8266 device with a new one
 * and the new gateway will still pick up the remote sensors which are still sending to the old MAC 
 */
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
void initVariant() {
  WiFi.mode(WIFI_AP);
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);
}

void setup() {
  Serial.begin(500000); Serial.println();

  Serial.print("This node AP mac: "); Serial.println(WiFi.softAPmacAddress());
  Serial.print("This node STA mac: "); Serial.println(WiFi.macAddress());

  initEspNow();
}

int heartBeat;

void loop() {
  if (millis()-heartBeat > 30000) {
    Serial.println("Waiting for ESP-NOW messages...");
    heartBeat = millis();
  }
}

void initEspNow() {
  if (esp_now_init()!=0) {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {

    // Investigate: There's little doc on what can be done within this method. If its like an ISR
    // then it should not take too long or do much I/O, but writing to Serial does appear to work ok

    //Serial.print("$$"); // $$ just an indicator that this line is a received ESP-Now message
    //Serial.write(mac, 6); // mac address of remote ESP-Now device
    //Serial.write(len);
     //Serial.print(data);
    //Serial.write(data, len); 

     
 //String s;
   //   for (int i=0; i < len; i++) s += char(data[i]);
     // Serial.println(s); 

String s = String(((char*)data));
      Serial.println(s);


     
  });
}
