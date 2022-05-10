// ----------------------------------------------------------------------------
// ESP-NOW network + WiFi gateway to the Internet
// ----------------------------------------------------------------------------
// ESP-NOW receiver acting as a WiFi gateway to the Internet
// ----------------------------------------------------------------------------



#include <WebServer.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Update.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include <WebSocketsServer.h>
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
String JSONtxt;
uint32_t last;
#include "webpahe.h"
#include "updateIndex.h"

int board1_volt=0;
int board2_volt=0;
int board3_volt=0;
float board1_Current=0;
float board2_Current=0;
float board3_Current=0;

boolean brd1S=false;
boolean brd2S=false;
boolean brd3S=false;
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


typedef struct led_message {
    int id;
    boolean State;
    

} led_message;
// Create a struct_message called BME280Readings to hold sensor readings

led_message relayboard_1;
led_message relayboard_2;
led_message relayboard_3;


struct_message myData;

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
//Burada üst kısımda belirlediğimiz statik ip ve gateway adreslerini ayarlıyoruz.
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

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {

    Serial.printf("received: %3u from %02x:%02x:%02x:%02x:%02x:%02x\n",
        (uint8_t) *data,
        mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]
    );

memcpy(&myData, data, sizeof(myData));
boardsStruct[myData.id-1].Volt = myData.Volt;

if(myData.id==1){
    board1_volt=myData.Volt;
    board1_Current=myData.Current;
    Serial.println(board1_Current);
  }
   else if(myData.id==2){
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
        Serial.println("ESP NOW pairing failure");
        while (1); }
        

    memcpy(peerInfo_2.peer_addr, ESP_NOW_RECEIVER_2, 6);
    if (esp_now_add_peer(&peerInfo_2) != ESP_OK) {
        Serial.println("ESP NOW pairing failure");
        while (1); }
       
/*
    memcpy(peerInfo.peer_addr, BRD2MAC, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("ESP NOW pairing failure");
        while (1); }        
*/
    
}


/*
 * Server Index Page


const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";
 */


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

    //1. led-----------------------------------------------
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

  
    if (millis() - last > 1000) {

  JSONtxt  = "{\"brd1V\":\""+board1volt+"\",\"brd1C\":\""+board1Current+"\",\"brd1S\":\""+BRD1status+"\",";
  JSONtxt +=  "\"brd2V\":\""+board2volt+"\",\"brd2C\":\""+board2Current+"\",\"brd2S\":\""+BRD2status+"\",";
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
