#include <Arduino.h>
#include <Filters.h>                      //This library does a massive work check it's .cpp file

#include <WebServer.h>
WebServer server(90);
#include <WiFi.h>
#include <WiFiClient.h>
#include <Update.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include "updateIndex.h"

#include <EEPROM.h>
#define EEPROM_SIZE 1

uint32_t last;

float ACS_Value;                              //Here we keep the raw data valuess
float testFrequency = 50;                    // test signal frequency (Hz)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist



float intercept = 0; // to be adjusted based on calibration testing
float slope = 0.016997792; // to be adjusted based on calibration testing
                      //Please check the ACS712 Tutorial video by SurtrTech to see how to get them because it depends on your sensor, or look below


float Amps_TRMS; // estimated actual current in amps

unsigned long printPeriod = 1000; // in milliseconds
// Track time in milliseconds since last reading 
unsigned long previousMillis = 0;


IPAddress local_IP(192, 168, 1, 45);
// Gateway IP adres
IPAddress gateway(192, 168, 1, 1);
//Subnet
IPAddress subnet(255, 255, 0, 0);

constexpr char WIFI_SSID[] = "FiberHGW_ZTXF6D_2.4GHz";
constexpr char WIFI_PASS[] = "tgzUCAdkAt";




const int analogVoltPin = 32;
#define ACS_Pin 35 
int gridVolt = 0;
int current =0;  
String success;
boolean RelayState;
int relaypin =26;
int relayledpin=19;
typedef struct struct_message {
    int id;
    int Volt;
    float Current;
    boolean State;

} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message myData;
struct_message board1;
// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

typedef struct led_message {
    int id;
    boolean State;
    

} led_message;
// Create a struct_message called BME280Readings to hold sensor readings

//led_message relayboard_1; //Her board için değişltirlecek
led_message relayboard_2;
// ----------------------------------------------------------------------------
// WiFi handling
// ----------------------------------------------------------------------------



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





void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {

    Serial.printf("received: %3u from %02x:%02x:%02x:%02x:%02x:%02x\n",
        (uint8_t) *data,
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]
    );

memcpy(&relayboard_2, data, sizeof(relayboard_2));

  RelayState=relayboard_2.State;
  EEPROM.write(0, RelayState);
  EEPROM.commit();
  Serial.println(RelayState);
  digitalWrite(relaypin, RelayState);
  digitalWrite(relayledpin, RelayState);
}

void initWiFi() {

    WiFi.mode(WIFI_MODE_APSTA);

    int32_t channel = getWiFiChannel(WIFI_SSID);

    // WiFi.printDiag(Serial);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
    // WiFi.printDiag(Serial);
     if (!WiFi.config(local_IP,gateway,subnet)) {
    Serial.println("Statik ip ve gateway adres ayarlama başarısız oldu.");
    }
//Wifi bağlantısını başlatıyoruz.    
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.printf("Bağlanılıyor :  %s .", WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(200); }
    Serial.println(" Wifi'a Bağlandı");

    IPAddress ip = WiFi.localIP();

    Serial.printf("SSID: %s\n", WIFI_SSID);
    Serial.printf("Channel: %u\n", WiFi.channel());
    Serial.printf("IP: %u.%u.%u.%u\n", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, ip >> 24);    
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
   esp_now_register_recv_cb(onReceive);
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
    pinMode(analogVoltPin,INPUT);
      pinMode(ACS_Pin,INPUT); 
    pinMode(relaypin,OUTPUT);
    pinMode(relayledpin,OUTPUT);
    EEPROM.begin(EEPROM_SIZE);
    RelayState = EEPROM.read(0);
    digitalWrite(relaypin, RelayState);
    digitalWrite(relayledpin, RelayState);
    delay(500);
    initWiFi();
    delay(500);
    initEspNow();
    delay(500);
    myData.id=2; // her board için değiştirilecek
    
    server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

  
  server.begin(); 
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------



void loop() {
  server.handleClient();
 // Serial.println(analogRead(analogCurrentPin));

  RunningStatistics inputStats;                 // create statistics to look at the raw test signal
  inputStats.setWindowSecs( windowLength );     //Set the window length
   
  while( true ) {   
    ACS_Value = analogRead(ACS_Pin);  // read the analog in value:
    inputStats.input(ACS_Value);  // log to Stats function
        
    if((unsigned long)(millis() - previousMillis) >= printPeriod) { //every second we do the calculation
      previousMillis = millis();   // update time
      
      Amps_TRMS = intercept + slope * inputStats.sigma();

      Serial.print( "\t Amps: " ); 
      Serial.println( Amps_TRMS );
      float watt = Amps_TRMS*220;
      myData.Current= Amps_TRMS;
      myData.Volt= watt;


    }
        if (millis() - last > 999) {
       
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

 
 /*if(millis()> lastSample +1 ){
  int thisSample=analogRead(analogCurrentPin);
      //sampleSum += sq(analogRead(analogCurrentPin)-1340);
      if(thisSample>sampleMax){
        sampleMax=thisSample;
      }
      if(thisSample<sampleMin){
        sampleMin=thisSample;
      }
      sampleCount++;   
      lastSample= millis();   
    }
    if(sampleCount==1000){
      //ortalama alma  //rms hesaplama 
      //float mean = sampleSum/sampleCount;
      //float value = sqrt(mean);
      float peakMv=sampleMax-sampleMin;
      //float avgMv=peakMv*0.707; //RMS
     
      //float factor=23.29411;
      float amper=peakMv;//avgMv/100;
      float watt = amper*220;
      myData.Current= amper;
      myData.Volt= watt;
      sampleCount=0;
      sampleMax=0;
    }
  */

  

}
