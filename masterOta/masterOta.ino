// ----------------------------------------------------------------------------
// ESP-NOW network + WiFi gateway to the Internet
// ----------------------------------------------------------------------------
// ESP-NOW receiver acting as a WiFi gateway to the Internet
// ----------------------------------------------------------------------------

#include <virtuabotixRTC.h> 
virtuabotixRTC myRTC(25, 12, 14);

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Update.h>
#include <esp_wifi.h>
#include <esp_now.h>

#include <WebServer.h>
#include <WebSocketsServer.h>
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

#include "webpahe.h"
#include "updateIndex.h"



//Variables of Board1

String brd1Mode=String("Manuel"); //Board'un Timer mode da mı Manuel Mode damı kullanılacağı bilgisinin kaydedileceği değişken (varsayılan manuel) 
int brd1m1basdk;
int brd1m1sondk; 
int brd1m2basdk;
int brd1m2sondk;
boolean brd1S=false;              //Board da bulunan rölenin durumu bilgisinin kaydedileceği değişken
int board1_volt=0;                //Board'un volt değeri bilgisinin kaydedileceği değişken
float board1_Current=0;           //Board'un akım değeri bilgisinin kaydedileceği değişken
uint32_t lastmessage1;            //Boarddan gelen en son mesajın zamanının kaydedileceği değişken
String brd1ConnectStatus = String("No Connection"); // Board'un bağlantı durumu bilgisinin kaydedileceği değişken
String JSONboard1;                // Board 1 ile ilgili bilgilerin JSON formatında kaydedileceği değişken (Bu değişken Websocket ile yayınlanacak)


//Variables of Board2

String brd2Mode=String("Manuel");
int brd2m1basdk;
int brd2m1sondk; 
int brd2m2basdk;
int brd2m2sondk;
boolean brd2S=false;
int board2_volt=0;
float board2_Current=0;
uint32_t lastmessage2;
String brd2ConnectStatus = String("No Connection");
String JSONboard2;



//Variables of Board3

String brd3Mode=String("Manuel");
int brd3m1basdk;
int brd3m1sondk; 
int brd3m2basdk;
int brd3m2sondk;
boolean brd3S=false;
int board3_volt=0;
float board3_Current=0;
uint32_t lastmessage3;
String brd3ConnectStatus = String("No Connection");
String JSONboard3;

//Variables of Board4

String brd4Mode=String("Manuel");
int brd4m1basdk;
int brd4m1sondk; 
int brd4m2basdk;
int brd4m2sondk;
boolean brd4S=false;
int board4_volt=0;
float board4_Current=0;
uint32_t lastmessage4;
String brd4ConnectStatus = String("No Connection");
String JSONboard4;


//Variables of Board5

String brd5Mode=String("Manuel");
int brd5m1basdk;
int brd5m1sondk; 
int brd5m2basdk;
int brd5m2sondk;
boolean brd5S=false;
int board5_volt=0;
float board5_Current=0;
uint32_t lastmessage5;
String brd5ConnectStatus = String("No Connection");
String JSONboard5;

//Variables of Board6

String brd6Mode=String("Manuel");
int brd6m1basdk;
int brd6m1sondk; 
int brd6m2basdk;
int brd6m2sondk;
boolean brd6S=false;
int board6_volt=0;
float board6_Current=0;
uint32_t lastmessage6;
String brd6ConnectStatus = String("No Connection");
String JSONboard6;


//Variables of Board7

String brd7Mode=String("Manuel");
int brd7m1basdk;
int brd7m1sondk; 
int brd7m2basdk;
int brd7m2sondk;
boolean brd7S=false;
int board7_volt=0;
float board7_Current=0;
uint32_t lastmessage7;
String brd7ConnectStatus = String("No Connection");
String JSONboard7;

//Variables of Board8

String brd8Mode=String("Manuel");
int brd8m1basdk;
int brd8m1sondk; 
int brd8m2basdk;
int brd8m2sondk;
boolean brd8S=false;
int board8_volt=0;
float board8_Current=0;
uint32_t lastmessage8;
String brd8ConnectStatus = String("No Connection");
String JSONboard8;


//Variables of Board9

String brd9Mode=String("Manuel");
int brd9m1basdk;
int brd9m1sondk; 
int brd9m2basdk;
int brd9m2sondk;
boolean brd9S=false;
int board9_volt=0;
float board9_Current=0;
uint32_t lastmessage9;
String brd9ConnectStatus = String("No Connection");
String JSONboard9;

//Variables of Board9

String brd10Mode=String("Manuel");
int brd10m1basdk;
int brd10m1sondk; 
int brd10m2basdk;
int brd10m2sondk;
boolean brd10S=false;
int board10_volt=0;
float board10_Current=0;
uint32_t lastmessage10;
String brd10ConnectStatus = String("No Connection");
String JSONboard10;

uint32_t last;




int LED =22;
int LED2 =5;
int LED3 =15;



void handleRoot()
{
  server.send(200,"text/html", webpageCont);
}


// ----------------------------------------------------------------------------
// WiFi handling
// ----------------------------------------------------------------------------


// Statik IP adres
IPAddress local_IP(192, 168, 1, 43);
// Gateway IP adres
IPAddress gateway(192, 168, 1, 1);
//Subnet
IPAddress subnet(255, 255, 0, 0);

constexpr char WIFI_SSID[] = "FiberHGW_ZTXF6D_2.4GHz";
constexpr char WIFI_PASS[] = "tgzUCAdkAt";


// Veri gÖnderme başarılı ise çağrılacak değişken
String success;
esp_now_peer_info_t peerInfo;
esp_now_peer_info_t peerInfo_2;
esp_now_peer_info_t peerInfo_3;
esp_now_peer_info_t peerInfo_4;
esp_now_peer_info_t peerInfo_5;
esp_now_peer_info_t peerInfo_6;
esp_now_peer_info_t peerInfo_7;
esp_now_peer_info_t peerInfo_8;
esp_now_peer_info_t peerInfo_9;
esp_now_peer_info_t peerInfo_10;
constexpr uint8_t ESP_NOW_RECEIVER[]   = { 0x24, 0x0A, 0xC4, 0x82, 0xAD, 0x18 };
//constexpr uint8_t ESP_NOW_RECEIVER[]   = { 0x30, 0xae, 0xa4, 0x00, 0x0d, 0x8c };
constexpr uint8_t ESP_NOW_RECEIVER_2[] = { 0x30, 0xAE, 0xA4, 0x00, 0x04, 0xb4 };
constexpr uint8_t ESP_NOW_RECEIVER_3[] = { 0x30, 0xAE, 0xA4, 0x00, 0x09, 0x50 };
constexpr uint8_t ESP_NOW_RECEIVER_4[] = { 0x30, 0xAE, 0xA4, 0x00, 0x3B, 0x08 };
constexpr uint8_t ESP_NOW_RECEIVER_5[] = { 0x30, 0xAE, 0xA4, 0x00, 0x09, 0x90 };
constexpr uint8_t ESP_NOW_RECEIVER_6[] = { 0x24, 0x6F, 0x28, 0xA0, 0xAF, 0x04 };
constexpr uint8_t ESP_NOW_RECEIVER_7[] = { 0x30, 0xAE, 0xA4, 0x00, 0x40, 0xBC };
constexpr uint8_t ESP_NOW_RECEIVER_8[] = { 0x24, 0x0A, 0xC4, 0x82, 0xAD, 0x14 };
constexpr uint8_t ESP_NOW_RECEIVER_9[] = { 0x30, 0xAE, 0xA4, 0x00, 0x02, 0xb4 };
constexpr uint8_t ESP_NOW_RECEIVER_10[] = { 0xCC, 0x50, 0xE3, 0x9A, 0x94, 0x94 };
//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int id;
    int Volt;
    float Current;
    boolean State;
    

} struct_message;

struct_message myData;

typedef struct led_message {
    int id;
    boolean State;
    

} led_message;

led_message relayboard_1;
led_message relayboard_2;
led_message relayboard_3;
led_message relayboard_4;
led_message relayboard_5;
led_message relayboard_6;
led_message relayboard_7;
led_message relayboard_8;
led_message relayboard_9;
led_message relayboard_10;

struct_message board1;
struct_message board2;
struct_message board3;
struct_message board4;
struct_message board5;
struct_message board6;
struct_message board7;
struct_message board8;
struct_message board9;
struct_message board10;



struct_message boardsStruct[10] = {board1, board2, board3, board4, board5, board6, board7, board8, board9, board10};





void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
Serial.println(payloadString);

  if(type == WStype_TEXT) //receive text from client
  {
    byte separator=payloadString.indexOf('=');
    byte separator2=payloadString.indexOf('=',separator+1);
    byte separator3=payloadString.indexOf('=',separator2+1);
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);
    String val2 = payloadString.substring(separator2+1,separator3-3);
    String val3 = payloadString.substring(separator3+1);

    if(var == "brd1time1")
    {
     brd1m1basdk= val2.toInt();
     brd1m1sondk= val3.toInt();
    }
    
    if(var == "brd1time2")
    {
     brd1m2basdk= val2.toInt();
     brd1m2sondk= val3.toInt();
    }


    if(var == "brd2time1")
    {
     brd2m1basdk= val2.toInt();
     brd2m1sondk= val3.toInt();
    }
    
    if(var == "brd2time2")
    {
     brd2m2basdk= val2.toInt();
     brd2m2sondk= val3.toInt();
    } 
       
    if(var == "brd3time1")
    {
     brd3m1basdk= val2.toInt();
     brd3m1sondk= val3.toInt();
    }
    
    if(var == "brd3time2")
    {
     brd3m2basdk= val2.toInt();
     brd3m2sondk= val3.toInt();
    }    

    if(var == "brd4time1")
    {
     brd4m1basdk= val2.toInt();
     brd4m1sondk= val3.toInt();
    }
    
    if(var == "brd4time2")
    {
     brd4m2basdk= val2.toInt();
     brd4m2sondk= val3.toInt();
    }    

    if(var == "brd5time1")
    {
     brd5m1basdk= val2.toInt();
     brd5m1sondk= val3.toInt();
    }
    
    if(var == "brd5time2")
    {
     brd5m2basdk= val2.toInt();
     brd5m2sondk= val3.toInt();
    }    

    if(var == "brd6time1")
    {
     brd6m1basdk= val2.toInt();
     brd6m1sondk= val3.toInt();
    }
    
    if(var == "brd6time2")
    {
     brd6m2basdk= val2.toInt();
     brd6m2sondk= val3.toInt();
    }    

    if(var == "brd7time1")
    {
     brd7m1basdk= val2.toInt();
     brd7m1sondk= val3.toInt();
    }
    
    if(var == "brd7time2")
    {
     brd7m2basdk= val2.toInt();
     brd7m2sondk= val3.toInt();
    }
        
    if(var == "brd8time1")
    {
     brd8m1basdk= val2.toInt();
     brd8m1sondk= val3.toInt();
    }
    
    if(var == "brd8time2")
    {
     brd8m2basdk= val2.toInt();
     brd8m2sondk= val3.toInt();
    } 
     
    if(var == "brd9time1")
    {
     brd9m1basdk= val2.toInt();
     brd9m1sondk= val3.toInt();
    }
    
    if(var == "brd9time2")
    {
     brd9m2basdk= val2.toInt();
     brd9m2sondk= val3.toInt();
    }  

    if(var == "brd10time1")
    {
     brd10m1basdk= val2.toInt();
     brd10m1sondk= val3.toInt();
    }
    
    if(var == "brd10time2")
    {
     brd10m2basdk= val2.toInt();
     brd10m2sondk= val3.toInt();
    }      
    
    
    if(var == "Mode1")
    {
      if(val == "Manuel"){
        brd1Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd1Mode = String("Timer");
      }
    }

    if(var == "Mode2")
    {
      if(val == "Manuel"){
        brd2Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd2Mode = String("Timer");
      }
    }
    
    if(var == "Mode3")
    {
      if(val == "Manuel"){
        brd3Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd3Mode = String("Timer");
      }
    }
        
    if(var == "Mode4")
    {
      if(val == "Manuel"){
        brd4Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd4Mode = String("Timer");
      }
    }

    if(var == "Mode5")
    {
      if(val == "Manuel"){
        brd5Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd5Mode = String("Timer");
      }
    }

    
    if(var == "Mode6")
    {
      if(val == "Manuel"){
        brd6Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd6Mode = String("Timer");
      }
    }
    
    if(var == "Mode7")
    {
      if(val == "Manuel"){
        brd7Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd7Mode = String("Timer");
      }
    }
    
    if(var == "Mode8")
    {
      if(val == "Manuel"){
        brd8Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd8Mode = String("Timer");
      }
    }

    if(var == "Mode9")
    {
      if(val == "Manuel"){
        brd9Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd9Mode = String("Timer");
      }
    }    

    if(var == "Mode10")
    {
      if(val == "Manuel"){
        brd10Mode = String("Manuel");
      }
      if(val == "Timer" ){
        brd10Mode = String("Timer");
      }
    }    
    
    if(var == "brd1S")
    {
      brd1S = false;
      if(val == "ON") brd1S = true;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
      //  Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
      
    }

    if(var == "brd2S")
    {
      brd2S = false;
      if(val == "ON") brd2S = true;
      relayboard_2.State=brd2S;
      relayboard_2.id=2;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_2, (uint8_t *) &relayboard_2, sizeof(relayboard_2));
        
        Serial.printf("sent: %3u on channel: %u\n", board2, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
      
    }

        if(var == "brd3S")
    {
      brd3S = false;
      if(val == "ON") brd3S = true;
      relayboard_3.State=brd3S;
      relayboard_3.id=3;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_3, (uint8_t *) &relayboard_3, sizeof(relayboard_3));
        
        Serial.printf("sent: %3u on channel: %u\n", board3, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }


        if(var == "brd4S")
    {
      brd4S = false;
      if(val == "ON") brd4S = true;
      relayboard_4.State=brd4S;
      relayboard_4.id=4;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_4, (uint8_t *) &relayboard_4, sizeof(relayboard_4));
        
        Serial.printf("sent: %3u on channel: %u\n", board4, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }
    

        if(var == "brd5S")
    {
      brd5S = false;
      if(val == "ON") brd5S = true;
      relayboard_5.State=brd5S;
      relayboard_5.id=5;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_5, (uint8_t *) &relayboard_5, sizeof(relayboard_5));
        
        Serial.printf("sent: %3u on channel: %u\n", board5, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }

    
        if(var == "brd6S")
    {
      brd6S = false;
      if(val == "ON") brd6S = true;
      relayboard_6.State=brd6S;
      relayboard_6.id=6;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_6, (uint8_t *) &relayboard_6, sizeof(relayboard_6));
        
        Serial.printf("sent: %3u on channel: %u\n", board6, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }

    
        if(var == "brd7S")
    {
      brd7S = false;
      if(val == "ON") brd7S = true;
      relayboard_7.State=brd7S;
      relayboard_7.id=7;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_7, (uint8_t *) &relayboard_7, sizeof(relayboard_7));
        
        Serial.printf("sent: %3u on channel: %u\n", board7, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }

    
        if(var == "brd8S")
    {
      brd8S = false;
      if(val == "ON") brd8S = true;
      relayboard_8.State=brd8S;
      relayboard_8.id=8;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_8, (uint8_t *) &relayboard_8, sizeof(relayboard_8));
        
        Serial.printf("sent: %3u on channel: %u\n", board8, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }

        if(var == "brd9S")
    {
      brd9S = false;
      if(val == "ON") brd9S = true;
      relayboard_9.State=brd9S;
      relayboard_9.id=9;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_9, (uint8_t *) &relayboard_9, sizeof(relayboard_9));
        
        Serial.printf("sent: %3u on channel: %u\n", board9, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }


        if(var == "brd10S")
    {
      brd10S = false;
      if(val == "ON") brd10S = true;
      relayboard_10.State=brd10S;
      relayboard_10.id=10;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_10, (uint8_t *) &relayboard_10, sizeof(relayboard_10));
        
        Serial.printf("sent: %3u on channel: %u\n", board10, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }      
    }    
        
  }



}


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








void initWiFi() {


//Burada wifi modunu hem access point hem station olarak ayarlıyoruz.
// (Access modu diğer esp kartlarının bu master karta ulaşması için. station modu yerel wifi ağına bağlanabilmek için)  
    WiFi.mode(WIFI_MODE_APSTA);
   int32_t channel = getWiFiChannel(WIFI_SSID);
   esp_wifi_set_promiscuous(true);
   esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
   esp_wifi_set_promiscuous(false);

/*
//Burada üst kısımda belirlediğimiz statik ip ve gateway adreslerini ayarlıyoruz.
     if (!WiFi.config(local_IP,gateway,subnet)) {
    Serial.println("Statik ip ve gateway adres ayarlama başarısız oldu.");
    }

*/

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

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {

    Serial.printf("received: %3u from %02x:%02x:%02x:%02x:%02x:%02x\n",
        (uint8_t) *data,
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]
    );

memcpy(&myData, data, sizeof(myData));

if(myData.id==1){
    brd1ConnectStatus=String("Connected");
    lastmessage1=millis();
    board1_volt=myData.Volt;
    board1_Current=myData.Current;
    Serial.println(board1_Current);
  }
   else if(myData.id==2){
    lastmessage2=millis();
    brd2ConnectStatus=String("Connected");
    board2_volt=myData.Volt;
    board2_Current=myData.Current;
  }
   else if(myData.id==3){
    lastmessage3=millis();
    brd3ConnectStatus=String("Connected");
    board3_volt=myData.Volt;
    board3_Current=myData.Current;
  }

   else if(myData.id==4){
    lastmessage4=millis();
    brd4ConnectStatus=String("Connected");
    board4_volt=myData.Volt;
    board4_Current=myData.Current;
  } 
  
   else if(myData.id==5){
    lastmessage5=millis();
    brd5ConnectStatus=String("Connected");
    board5_volt=myData.Volt;
    board5_Current=myData.Current;
  }   

   else if(myData.id==6){
    lastmessage6=millis();
    brd6ConnectStatus=String("Connected");
    board6_volt=myData.Volt;
    board6_Current=myData.Current;
  }
   else if(myData.id==7){
    lastmessage7=millis();
    brd7ConnectStatus=String("Connected");
    board7_volt=myData.Volt;
    board7_Current=myData.Current;
  }  
  
   else if(myData.id==8){
    lastmessage8=millis();
    brd8ConnectStatus=String("Connected");
    board8_volt=myData.Volt;
    board8_Current=myData.Current;
  }  

   else if(myData.id==9){
    lastmessage9=millis();
    brd9ConnectStatus=String("Connected");
    board9_volt=myData.Volt;
    board9_Current=myData.Current;
  }

   else if(myData.id==10){
    lastmessage10=millis();
    brd10ConnectStatus=String("Connected");
    board10_volt=myData.Volt;
    board10_Current=myData.Current;
  }     

      
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

void initEspNow() {
// ESP-NOW'ı başlatıyoruz
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP NOW Başlatılamadı");
        while (1);
    }

    esp_now_register_recv_cb(onReceive);
    esp_now_register_send_cb(OnDataSent);
    
    
    memcpy(peerInfo.peer_addr, ESP_NOW_RECEIVER, 6);
    peerInfo.ifidx   = WIFI_IF_STA;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("ESP NOW 1 pairing failure");
        while (1); }
        

    memcpy(peerInfo_2.peer_addr, ESP_NOW_RECEIVER_2, 6);
    if (esp_now_add_peer(&peerInfo_2) != ESP_OK) {
        Serial.println("ESP NOW 2 pairing failure");
        while (1); }

    memcpy(peerInfo_3.peer_addr, ESP_NOW_RECEIVER_3, 6);
    if (esp_now_add_peer(&peerInfo_3) != ESP_OK) {
        Serial.println("ESP NOW 3 pairing failure");
        while (1); }    

            
    memcpy(peerInfo_4.peer_addr, ESP_NOW_RECEIVER_4, 6);
    if (esp_now_add_peer(&peerInfo_4) != ESP_OK) {
        Serial.println("ESP NOW 4 pairing failure");
        while (1); } 


    memcpy(peerInfo_5.peer_addr, ESP_NOW_RECEIVER_5, 6);
    if (esp_now_add_peer(&peerInfo_5) != ESP_OK) {
        Serial.println("ESP NOW 5 pairing failure");
        while (1); } 

        
    memcpy(peerInfo_6.peer_addr, ESP_NOW_RECEIVER_6, 6);
    if (esp_now_add_peer(&peerInfo_6) != ESP_OK) {
        Serial.println("ESP NOW 6 pairing failure");
        while (1); } 

        
    memcpy(peerInfo_7.peer_addr, ESP_NOW_RECEIVER_7, 6);
    if (esp_now_add_peer(&peerInfo_7) != ESP_OK) {
        Serial.println("ESP NOW 7 pairing failure");
        while (1); }   
                             
    memcpy(peerInfo_8.peer_addr, ESP_NOW_RECEIVER_8, 6);
    if (esp_now_add_peer(&peerInfo_8) != ESP_OK) {
        Serial.println("ESP NOW 8 pairing failure");
        while (1); }   

    memcpy(peerInfo_9.peer_addr, ESP_NOW_RECEIVER_9, 6);
    if (esp_now_add_peer(&peerInfo_9) != ESP_OK) {
        Serial.println("ESP NOW 9 pairing failure");
        while (1); }        

    memcpy(peerInfo_10.peer_addr, ESP_NOW_RECEIVER_10, 6);
    if (esp_now_add_peer(&peerInfo_10) != ESP_OK) {
        Serial.println("ESP NOW 10 pairing failure");
        while (1); }

        
/*
    memcpy(peerInfo.peer_addr, BRD2MAC, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("ESP NOW pairing failure");
        while (1); }        
*/
    
}




// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(500);
    
    pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);


    initWiFi();
// ESP-NOW'ı başlatıyoruz
    initEspNow();


  server.on("/", handleRoot);


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

  
  server.begin(); webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------

void loop() {
    
webSocket.loop(); server.handleClient();

myRTC.updateTime();
int saat= myRTC.hours;
int dkk = myRTC.minutes;
int dk= saat * 60 + dkk;




String board1volt = String(board1_volt);
String board2volt = String(board2_volt);
String board3volt = String(board3_volt);
String board4volt = String(board4_volt);
String board5volt = String(board5_volt);
String board6volt = String(board6_volt);
String board7volt = String(board7_volt);
String board8volt = String(board8_volt);
String board9volt = String(board9_volt);
String board10volt = String(board10_volt);


String board1Current = String(board1_Current);
String board2Current = String(board2_Current);
String board3Current = String(board3_Current);
String board4Current = String(board4_Current);
String board5Current = String(board5_Current);
String board6Current = String(board6_Current);
String board7Current = String(board7_Current);
String board8Current = String(board8_Current);
String board9Current = String(board9_Current);
String board10Current = String(board10_Current);


//String strtbrd3ConnectStatus = String(brd3ConnectStatus);
//String strtbrd1ConnectStatus = String(brd1ConnectStatus);


    //1. board-----------------------------------------------
  if(brd1S == false) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
  //-----------------------------------------------
  
  String BRD1status = "OFF";
  if(brd1S == true ) BRD1status = "ON";

      //2. led-----------------------------------------------
  if(brd2S == false) digitalWrite(LED2, LOW);
  else digitalWrite(LED2, HIGH);
  //-----------------------------------------------
  String BRD2status = "OFF";
  if(brd2S == true) BRD2status = "ON";


      //3. led-----------------------------------------------
  if(brd3S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD3status = "OFF";
  if(brd3S == true) BRD3status = "ON";

      //4. led-----------------------------------------------
  if(brd4S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD4status = "OFF";
  if(brd4S == true) BRD4status = "ON";  


      //5. led-----------------------------------------------
  if(brd5S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD5status = "OFF";
  if(brd5S == true) BRD5status = "ON";   

  
      //6. led-----------------------------------------------
  if(brd6S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD6status = "OFF";
  if(brd6S == true) BRD6status = "ON";   
  
      //7. led-----------------------------------------------
  if(brd7S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD7status = "OFF";
  if(brd7S == true) BRD7status = "ON";   

      //8. led-----------------------------------------------
  if(brd8S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD8status = "OFF";
  if(brd8S == true) BRD8status = "ON";  

      //9. led-----------------------------------------------
  if(brd9S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD9status = "OFF";
  if(brd9S == true) BRD9status = "ON";  


      //10. led-----------------------------------------------
  if(brd10S == false) digitalWrite(LED3, LOW);
  else digitalWrite(LED3, HIGH);
  //-----------------------------------------------
  String BRD10status = "OFF";
  if(brd10S == true) BRD10status = "ON";




    
    if (millis() - lastmessage1 > 5000) {
    brd1ConnectStatus=String("No Connection");
  }

  if (millis() - lastmessage2 > 5000) {
    brd2ConnectStatus=String("No Connection");
  }

  
  if (millis() - lastmessage3 > 5000) {
    brd3ConnectStatus=String("No Connection");
  }
  
  if (millis() - lastmessage4 > 5000) {
    brd4ConnectStatus=String("No Connection");
  }  

  
  if (millis() - lastmessage5 > 5000) {
    brd5ConnectStatus=String("No Connection");
  }    
  
  if (millis() - lastmessage6 > 5000) {
    brd6ConnectStatus=String("No Connection");
  } 
  
  if (millis() - lastmessage7 > 5000) {
    brd7ConnectStatus=String("No Connection");
  } 

  if (millis() - lastmessage8 > 5000) {
    brd8ConnectStatus=String("No Connection");
  } 

  if (millis() - lastmessage9 > 5000) {
    brd9ConnectStatus=String("No Connection");
  }  

  if (millis() - lastmessage10 > 5000) {
    brd10ConnectStatus=String("No Connection");
  }   
  
  
    if (millis() - last > 1000) {
Serial.println(brd3ConnectStatus);
Serial.println(dk);
Serial.print("bas1:");
Serial.println(brd3m1basdk);
Serial.print("son1:");
Serial.println(brd3m1sondk);
Serial.print("bas2:");
Serial.println(brd3m2basdk);
Serial.print("son2:");
Serial.println(brd3m2sondk);

  JSONboard1  = "{\"brd1M\":\""+brd1Mode+"\",";
  JSONboard1 +=  "\"brd1V\":\""+board1volt+"\",";
  JSONboard1 +=  "\"brd1C\":\""+board1Current+"\",";
  JSONboard1 +=  "\"brd1S\":\""+BRD1status+"\",";
  JSONboard1 +=  "\"brd1ConnectSt\":\""+brd1ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard1);


  JSONboard2  = "{\"brd2M\":\""+brd2Mode+"\",";
  JSONboard2 +=  "\"brd2V\":\""+board2volt+"\",";
  JSONboard2 +=  "\"brd2C\":\""+board2Current+"\",";
  JSONboard2 +=  "\"brd2S\":\""+BRD2status+"\",";
  JSONboard2 +=  "\"brd2ConnectSt\":\""+brd2ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard2);  


  JSONboard3  = "{\"brd3M\":\""+brd3Mode+"\",";
  JSONboard3 +=  "\"brd3V\":\""+board3volt+"\",";
  JSONboard3 +=  "\"brd3C\":\""+board3Current+"\",";
  JSONboard3 +=  "\"brd3S\":\""+BRD3status+"\",";
  JSONboard3 +=  "\"brd3ConnectSt\":\""+brd3ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard3);  


  JSONboard4  = "{\"brd4M\":\""+brd4Mode+"\",";
  JSONboard4 +=  "\"brd4V\":\""+board4volt+"\",";
  JSONboard4 +=  "\"brd4C\":\""+board4Current+"\",";
  JSONboard4 +=  "\"brd4S\":\""+BRD4status+"\",";
  JSONboard4 +=  "\"brd4ConnectSt\":\""+brd4ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard4);    


  JSONboard5  = "{\"brd5M\":\""+brd5Mode+"\",";
  JSONboard5 +=  "\"brd5V\":\""+board5volt+"\",";
  JSONboard5 +=  "\"brd5C\":\""+board5Current+"\",";
  JSONboard5 +=  "\"brd5S\":\""+BRD5status+"\",";
  JSONboard5 +=  "\"brd5ConnectSt\":\""+brd5ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard5);   


  JSONboard6  = "{\"brd6M\":\""+brd6Mode+"\",";
  JSONboard6 +=  "\"brd6V\":\""+board6volt+"\",";
  JSONboard6 +=  "\"brd6C\":\""+board6Current+"\",";
  JSONboard6 +=  "\"brd6S\":\""+BRD6status+"\",";
  JSONboard6 +=  "\"brd6ConnectSt\":\""+brd6ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard6);     

  
  JSONboard7  = "{\"brd7M\":\""+brd7Mode+"\",";
  JSONboard7 +=  "\"brd7V\":\""+board7volt+"\",";
  JSONboard7 +=  "\"brd7C\":\""+board7Current+"\",";
  JSONboard7 +=  "\"brd7S\":\""+BRD7status+"\",";
  JSONboard7 +=  "\"brd7ConnectSt\":\""+brd7ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard7);   

  
  JSONboard8  = "{\"brd8M\":\""+brd8Mode+"\",";
  JSONboard8 +=  "\"brd8V\":\""+board8volt+"\",";
  JSONboard8 +=  "\"brd8C\":\""+board8Current+"\",";
  JSONboard8 +=  "\"brd8S\":\""+BRD8status+"\",";
  JSONboard8 +=  "\"brd8ConnectSt\":\""+brd8ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard8);  


  JSONboard9  = "{\"brd9M\":\""+brd9Mode+"\",";
  JSONboard9 +=  "\"brd9V\":\""+board9volt+"\",";
  JSONboard9 +=  "\"brd9C\":\""+board9Current+"\",";
  JSONboard9 +=  "\"brd9S\":\""+BRD9status+"\",";
  JSONboard9 +=  "\"brd9ConnectSt\":\""+brd9ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard9); 


  JSONboard10  = "{\"brd10M\":\""+brd10Mode+"\",";
  JSONboard10 +=  "\"brd10V\":\""+board10volt+"\",";
  JSONboard10 +=  "\"brd10C\":\""+board10Current+"\",";
  JSONboard10 +=  "\"brd10S\":\""+BRD10status+"\",";
  JSONboard10 +=  "\"brd10ConnectSt\":\""+brd10ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard10);
     
///////////////////////////////////////////////////
////////////////////////////////////////////////
//TIME For Board1 
/////////////////////////////////////////////////

if (brd1m1basdk <= dk && brd1m1sondk >= dk && brd1Mode == "Timer"){
  brd1S=true;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
        //Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if (brd1m2basdk <= dk && brd1m2sondk >= dk && brd1Mode == "Timer"){
  brd1S=true;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
        //Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if(brd1Mode == "Timer"){
if(dk > brd1m2sondk || dk < brd1m1basdk) {
  brd1S=false;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
       // Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}

if(dk < brd1m2sondk || dk > brd1m1basdk) {
  brd1S=false;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
       // Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}}


///////////////////////////////////////////////////
////////////////////////////////////////////////
//END OF TIME For Board1 
/////////////////////////////////////////////////


///////////////////////////////////////////////////
////////////////////////////////////////////////
//TIME For Board  2  
/////////////////////////////////////////////////

if (brd2m1basdk <= dk && brd2m1sondk >= dk && brd2Mode == "Timer"){
  brd2S=true;
      relayboard_2.State=brd2S;
      relayboard_2.id=2;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_2, (uint8_t *) &relayboard_2, sizeof(relayboard_2));
        
        //Serial.printf("sent: %3u on channel: %u\n", board2, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if (brd2m2basdk <= dk && brd2m2sondk >= dk && brd2Mode == "Timer"){
  brd2S=true;
      relayboard_2.State=brd2S;
      relayboard_2.id=2;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_2, (uint8_t *) &relayboard_2, sizeof(relayboard_2));
        
        //Serial.printf("sent: %3u on channel: %u\n", board2, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if(brd2Mode == "Timer"){
if(dk > brd2m2sondk || dk < brd2m1basdk) {
  brd2S=false;
      relayboard_2.State=brd2S;
      relayboard_2.id=2;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_2, (uint8_t *) &relayboard_2, sizeof(relayboard_2));
        
       // Serial.printf("sent: %3u on channel: %u\n", board2, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}

if(dk < brd2m2sondk || dk > brd2m1basdk) {
  brd2S=false;
      relayboard_2.State=brd2S;
      relayboard_2.id=2;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_2, (uint8_t *) &relayboard_2, sizeof(relayboard_2));
        
       // Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}}

///////////////////////////////////////////////////
////////////////////////////////////////////////
//END OF TIME For Board  2
/////////////////////////////////////////////////



///////////////////////////////////////////////////
////////////////////////////////////////////////
//END OF TIME For Board  3
/////////////////////////////////////////////////


if (brd3m1basdk <= dk && brd3m1sondk >= dk && brd3Mode == "Timer"){
  brd3S=true;
      relayboard_3.State=brd3S;
      relayboard_3.id=3;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_3, (uint8_t *) &relayboard_3, sizeof(relayboard_3));
        
        //Serial.printf("sent: %3u on channel: %u\n", board3, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if (brd3m2basdk <= dk && brd3m2sondk >= dk && brd3Mode == "Timer"){
  brd3S=true;
      relayboard_3.State=brd3S;
      relayboard_3.id=3;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_3, (uint8_t *) &relayboard_3, sizeof(relayboard_3));
        
        //Serial.printf("sent: %3u on channel: %u\n", board3, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}
else if(brd3Mode == "Timer"){
if(dk > brd3m2sondk || dk < brd3m1basdk) {
  brd3S=false;
      relayboard_3.State=brd3S;
      relayboard_3.id=3;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_3, (uint8_t *) &relayboard_3, sizeof(relayboard_3));
        
       // Serial.printf("sent: %3u on channel: %u\n", board3, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}

if(dk < brd3m2sondk || dk > brd3m1basdk) {
  brd3S=false;
      relayboard_3.State=brd3S;
      relayboard_3.id=3;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER_3, (uint8_t *) &relayboard_3, sizeof(relayboard_3));
        
       // Serial.printf("sent: %3u on channel: %u\n", board3, WiFi.channel());
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      }
    else {
      Serial.println("Error sending the data");
         }
}}





          last = millis();
    }

   


}
