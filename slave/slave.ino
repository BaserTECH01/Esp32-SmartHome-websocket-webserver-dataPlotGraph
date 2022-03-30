#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>

const int analogInPin = 35;
int gridVolt = 0;  
String success;

typedef struct struct_message {
    int id;
    int Volt;

} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message myData;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// ----------------------------------------------------------------------------
// WiFi handling
// ----------------------------------------------------------------------------

constexpr char WIFI_SSID[] = "FiberHGW_ZTXF6D_2.4GHz";

int32_t getWiFiChannel(const char *ssid) {

    if (int32_t n = WiFi.scanNetworks()) {
        for (uint8_t i=0; i<n; i++) {
            if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
                return WiFi.channel(i);
            }
        }
    }

    return 0;
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}


void initWiFi() {

    WiFi.mode(WIFI_MODE_STA);

    int32_t channel = getWiFiChannel(WIFI_SSID);

    // WiFi.printDiag(Serial);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
    // WiFi.printDiag(Serial);
}

// ----------------------------------------------------------------------------
// ESP-NOW handling
// ----------------------------------------------------------------------------

constexpr uint8_t ESP_NOW_RECEIVER[] = { 0x24, 0x6f, 0x28, 0xa0, 0xaf, 0x05 };

esp_now_peer_info_t peerInfo;

void initEspNow() {

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP NOW failed to initialize");
        while (1);
    }
   esp_now_register_send_cb(OnDataSent);
   
    memcpy(peerInfo.peer_addr, ESP_NOW_RECEIVER, 6);
    peerInfo.ifidx   = WIFI_IF_STA;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("ESP NOW pairing failure");
        while (1);
    }
}

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

void setup() {
    Serial.begin(115200);

    initWiFi();
    initEspNow();
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------

uint32_t last;

void loop() {
  getReadings();
  myData.id=2;
  myData.Volt = gridVolt;
    if (millis() - last > 500) {
        
        
        esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &myData, sizeof(myData));
        
        Serial.printf("sent: %3u on channel: %u\n", myData, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
        last = millis();
    }
}

void getReadings(){
    gridVolt = analogRead(analogInPin);

}
