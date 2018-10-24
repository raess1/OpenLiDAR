/*
 */
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LIDARLite.h>
extern "C" {
#include <espnow.h>
}


// Change the MAC Address to the receiver ESP(s) that will receive the messages from your sending ESP8266
uint8_t recMAC[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};

#define WIFI_CHANNEL 1                                                         // Set channel from 1 to 14      
                                                  

#define MSG_LEN 40
struct __attribute__((packed)) MSG {                                          
  char text[MSG_LEN];
  unsigned long value;
};
MSG radarMsg;
int msgSize = sizeof(radarMsg);                                                  // NOTE:  must be less than 250 bytes!

//lidar
boolean            lastRadarState = 0;
unsigned long      radarCount = 0;
LIDARLite myLidarLite;



void setup() {

  Wire.begin(D4, D1);
  Serial.begin(500000);
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations

  Serial.println("\nStarting ESP-NOW Sender");
  
  WiFi.mode(WIFI_STA);                                                          // Place in station mode for ESP-NOW sensor node
  WiFi.disconnect();                                                            // Make sure disconnected from WiFi

  Serial.print("Sender MAC:   ");                                               // Serial print sender MAC
  Serial.println(WiFi.macAddress().c_str());
  Serial.print("Receiver MAC: ");                                               // Serial print receiver MAC
  for (int i = 0; i < 6; i++){
    Serial.print(recMAC[i], HEX);
    if (i < 5){
      Serial.print(":");
    }
  }
  Serial.print(", channel: ");                                                  // Serial print the channel
  Serial.println(WIFI_CHANNEL);
  Serial.println("");

  if (esp_now_init() != 0) {                                                    // Halt execution if init failed
    Serial.println("ESP-NOW init failed");
    while(1);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);                               // Sender is in controller role
  esp_now_add_peer(recMAC, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);          // Sends to MAC of receiver in slave role



}


void loop() {

  // Lidar
  strcpy(radarMsg.text, ":");                                   // Initialize the text messages                                
  radarMsg.value = myLidarLite.distance();                                                           // and values to be sent
  //Serial.println("Lidar set up");
  unsigned char store[msgSize];                                                     // ESP-NOW buffer stored as unsigned char

      radarCount++;
      //Serial.print(radarMsg.text);
      //Serial.println(radarMsg.value);
      memcpy(&store, &radarMsg, msgSize);                                           // for transmission (req'd by ESP-NOW)
      esp_now_send(NULL, store, msgSize);                                           // NULL sends to all peers
  delay(0);
}
