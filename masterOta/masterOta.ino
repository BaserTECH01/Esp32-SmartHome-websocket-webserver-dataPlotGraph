// ----------------------------------------------------------------------------
// ESP-NOW network + WiFi gateway to the Internet
// ----------------------------------------------------------------------------
// ESP-NOW receiver acting as a WiFi gateway to the Internet
// ----------------------------------------------------------------------------




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
String brdmode1="0";              //birinci zaman
boolean brd1S=false;              //Board da bulunan rölenin durumu bilgisinin kaydedileceği değişken
int board1_volt=0;                //Board'un volt değeri bilgisinin kaydedileceği değişken
float board1_Current=0;           //Board'un akım değeri bilgisinin kaydedileceği değişken
uint32_t lastmessage1;            //Boarddan gelen en son mesajın zamanının kaydedileceği değişken
String brd1ConnectStatus = String("No Connection"); // Board'un bağlantı durumu bilgisinin kaydedileceği değişken
String JSONboard1;                // Board 1 ile ilgili bilgilerin JSON formatında kaydedileceği değişken (Bu değişken Websocket ile yayınlanacak)

String JSONtxt;

uint32_t last;

uint32_t lastmessage2;

String brd2Mode=String("Manuel");


int board2_volt=0;
int board3_volt=0;


float board2_Current=0;
float board3_Current=0;


boolean brd2S=false;
boolean brd3S=false;

String brd2ConnectStatus = String("No Connection");
String brd3ConnectStatus = String("No Connection");

int LED =4;
int LED2 =5;
int LED3 =18;



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

constexpr uint8_t ESP_NOW_RECEIVER[] = { 0x30, 0xAE, 0xA4, 0x00, 0x40, 0xBC };
constexpr uint8_t ESP_NOW_RECEIVER_2[] = { 0x30, 0xAE, 0xA4, 0x00, 0x3B, 0x08 };
uint8_t BRD2MAC[] = {0x7C, 0x9E, 0xBD, 0x37, 0x28, 0x4C};
uint8_t BRD3MAC[] = {0x7C, 0x9E, 0xBD, 0x37, 0x28, 0x4C};
uint8_t BRD4MAC[] = {0x7C, 0x9E, 0xBD, 0x37, 0x28, 0x4C};


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




struct_message board1;
struct_message board2;
struct_message board3;

struct_message boardsStruct[3] = {board1, board2, board3};




void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;


  if(type == WStype_TEXT) //receive text from client
  {
    byte separator=payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);


    if(var == "Mode1")
    {
      if(val == "Manuel") brd1Mode = String("Manuel");
      if(val == "Timer" ) brd1Mode = String("Timer");
    }

    if(var == "brd1S")
    {
      brd1S = false;
      if(val == "ON") brd1S = true;
      relayboard_1.State=brd1S;
      relayboard_1.id=1;
      esp_err_t result = esp_now_send(ESP_NOW_RECEIVER, (uint8_t *) &relayboard_1, sizeof(relayboard_1));
        
        Serial.printf("sent: %3u on channel: %u\n", board1, WiFi.channel());
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
    }


    if(var == "inputbrd1")
    {
      brdmode1 = val;
      Serial.println(brdmode1);
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
boardsStruct[myData.id-1].Volt = myData.Volt;

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
    board3_volt=myData.Volt;
    board3_Current=myData.Current;
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

String board1volt = String(board1_volt);
String board2volt = String(board2_volt);
String board3volt = String(board3_volt);

String board1Current = String(board1_Current);
String board2Current = String(board2_Current);
String board3Current = String(board3_Current);

String strtbrd1ConnectStatus = String(brd1ConnectStatus);


    //1. board-----------------------------------------------
  if(brd1S == false) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
  //-----------------------------------------------
  String BRD1status = "OFF";
  if(brd1S == true) BRD1status = "ON";

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


  if (millis() - lastmessage2 > 5000) {
    brd2ConnectStatus=String("No Connection");
  }

    if (millis() - lastmessage1 > 5000) {
    brd1ConnectStatus=String("No Connection");
  }
    if (millis() - last > 1000) {
Serial.print(brd2ConnectStatus);
Serial.println(brdmode1);

  JSONboard1  = "{\"brd1M\":\""+brd1Mode+"\",";
  JSONboard1 +=  "\"brd1V\":\""+board1volt+"\",";
  JSONboard1 +=  "\"brd1C\":\""+board1Current+"\",";
  JSONboard1 +=  "\"brd1S\":\""+BRD1status+"\",";
  JSONboard1 +=  "\"brd1ConnectSt\":\""+brd1ConnectStatus+"\"    }";

                
  webSocket.broadcastTXT(JSONboard1);
  
  
  JSONtxt =  "{\"brd2V\":\""+board2volt+"\",\"brd2C\":\""+board2Current+"\",\"brd2S\":\""+BRD2status+"\",\"brd2ConnectSt\":\""+brd2ConnectStatus+"\",";
  JSONtxt +=  "\"brd3V\":\""+board3volt+"\",\"brd3C\":\""+board3Current+"\",\"brd3S\":\""+BRD3status+"\"}";
  
  webSocket.broadcastTXT(JSONtxt);

          last = millis();
    }
 /*
  JSONtxt2 = "{\"board2\":\""+board2volt+"\"}";
  webSocket.broadcastTXT(JSONtxt2); 

  JSONtxt3 = "{\"board3\":\""+board3volt+"\"}";
  webSocket.broadcastTXT(JSONtxt3);   
  */
   /*
  Serial.print("board 1 :");
  Serial.print(board1_volt);
  Serial.print("\t");
  Serial.print("board 2 :");
  Serial.print(board2_volt);
  Serial.print("\t");
  Serial.print("board 3 :");
  Serial.print(board3_volt);
  Serial.println();

  */
   


}
