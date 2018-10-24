/**
 */
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include "user_interface.h"
}
#define MSG_LEN 40
struct __attribute__((packed)) MSG {                                          
  char text[MSG_LEN];
  unsigned long value;
  unsigned int led;
} msg;
int msgSize = sizeof(msg);
volatile boolean haveMsg = false;                                               // Volatile flag when new msg is received
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

  if (esp_now_init() != 0) {                                                    // Halt execution if init failed
    Serial.println("ESP-NOW init failed");
    while(1);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);                                    // slave is receiver only
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {       // call back (interrupt) when
                                                            // message is received stores
  
    memcpy(&msg, data, sizeof(msg));                                            // call back also stores the msg
    haveMsg = true;                                                             // flag that msg was received
  });
}


void loop() {
    if (haveMsg == true){                                                         // If a msg has been received
    
    //Serial.print(msg.text);
    Serial.println(msg.value);


    
    }
    
    haveMsg = false;                                                           // and set the msg flag to false
  }


  
