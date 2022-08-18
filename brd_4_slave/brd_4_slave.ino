#include <Arduino.h>
#include <Filters.h>                      //This library does a massive work check it's .cpp file


#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>

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







const int analogVoltPin = 32;
#define ACS_Pin 35 
int gridVolt = 0;
int current =0;  
String success;
boolean RelayState;
int relaypin =26;
int relayledpin=19;
int peerpin=18;
int peerstate=0;
typedef struct struct_message {
    int id;
    int Volt;
    float Current;
    boolean State;

} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message myData;
struct_message board4;
// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

typedef struct led_message {
    int id;
    boolean State;
    

} led_message;
// Create a struct_message called BME280Readings to hold sensor readings

led_message relayboard_4; //Her board için değişltirlecek

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
    digitalWrite(5,0);
    digitalWrite(peerpin,1);
  }
  else{
    digitalWrite(5,1);
    success = "Delivery Fail :(";
    digitalWrite(5,1);
    digitalWrite(peerpin,0);
    
  }
}





void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {

    Serial.printf("received: %3u from %02x:%02x:%02x:%02x:%02x:%02x\n",
        (uint8_t) *data,
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]
    );

memcpy(&relayboard_4, data, sizeof(relayboard_4));

  RelayState=relayboard_4.State;
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
}

// ----------------------------------------------------------------------------
// ESP-NOW handling
// ----------------------------------------------------------------------------

constexpr uint8_t ESP_NOW_RECEIVER[] = { 0x30, 0xAE, 0xA4, 0x00, 0x0D, 0x8C };

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
    pinMode(peerpin,OUTPUT);
    pinMode(5,OUTPUT);
    EEPROM.begin(EEPROM_SIZE);
    RelayState = EEPROM.read(0);
    digitalWrite(relaypin, RelayState);
    digitalWrite(relayledpin, RelayState);
    initWiFi();
    initEspNow();
    myData.id=4; // her board için değiştirilecek
    digitalWrite(5,1);
   
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------



void loop() {

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
