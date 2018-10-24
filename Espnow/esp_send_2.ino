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
                                                  

// Set up a struct to store the text and numbers that will be sent - use packed for the smallest possible alignment for bytes
// All receiving ESP(s) must also have this structure.






// keep in sync with slave struct
struct __attribute__((packed)) SENSOR_DATA {
    float lidar;
} sensorData;

LIDARLite myLidarLite;



void setup() {

  Wire.begin(D4, D1);
  Serial.begin(115200);
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
  readLIDARLite();
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

void readLIDARLite() {
  sensorData.lidar = myLidarLite.distance();
  Serial.printf("lidar=%01f", sensorData.lidar);
}

void loop() {

  uint8_t bs[sizeof(sensorData)];
  memcpy(bs, &sensorData, sizeof(sensorData));
  esp_now_send(NULL, bs, sizeof(sensorData)); // NULL means send to all peers
}
  
