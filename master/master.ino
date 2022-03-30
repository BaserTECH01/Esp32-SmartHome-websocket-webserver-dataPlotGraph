// ----------------------------------------------------------------------------
// ESP-NOW network + WiFi gateway to the Internet
// ----------------------------------------------------------------------------
// ESP-NOW receiver acting as a WiFi gateway to the Internet
// ----------------------------------------------------------------------------



#include <WebServer.h>
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <WebSocketsServer.h>
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
String JSONtxt1;
String JSONtxt2;
String JSONtxt3;
#include "webpahe.h"

void handleRoot()
{
  server.send(200,"text/html", webpageCont);
}


// ----------------------------------------------------------------------------
// WiFi handling
// ----------------------------------------------------------------------------

int board1_volt=0;
int board2_volt=0;
int board3_volt=0;

// Statik IP adres
IPAddress local_IP(192, 168, 1, 43);
// Gateway IP adresi
IPAddress gateway(192, 168, 1, 1);
//Subnet
IPAddress subnet(255, 255, 0, 0);

constexpr char WIFI_SSID[] = "FiberHGW_ZTXF6D_2.4GHz";
constexpr char WIFI_PASS[] = "tgzUCAdkAt";


// Veri gÖnderme başarılı ise çağrılacak değişken
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int id;
    int Volt;

} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message myData;

struct_message board1;
struct_message board2;
struct_message board3;

struct_message boardsStruct[3] = {board1, board2, board3};

esp_now_peer_info_t peerInfo;



void initWiFi() {


//Burada wifi modunu hem access point hem station olarak ayarlıyoruz.
// (Access modu diğer esp kartlarının bu master karta ulaşması için. station modu yerel wifi ağına bağlanabilmek için)  
    WiFi.mode(WIFI_MODE_APSTA);

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
  }
   else if(myData.id==2){
    board2_volt=myData.Volt;
  }
   else if(myData.id==3){
    board3_volt=myData.Volt;
  }
}

void initEspNow() {
// ESP-NOW'ı başlatıyoruz
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP NOW Başlatılamadı");
        while (1);
    }

    esp_now_register_recv_cb(onReceive);
}

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

void setup() {
    Serial.begin(115200);
    delay(500);

    initWiFi();
// ESP-NOW'ı başlatıyoruz
    initEspNow();


  server.on("/", handleRoot);
  server.begin(); webSocket.begin();
}

// ----------------------------------------------------------------------------
// Main control loop
// ----------------------------------------------------------------------------

void loop() {
  
  webSocket.loop(); server.handleClient();

String board1volt = String(board1_volt);
String board2volt = String(board2_volt);
String board3volt = String(board3_volt);
  JSONtxt1 = "{\"board1\":\""+board1volt+"\",\"board2\":\""+board2volt+"\",\"board3\":\""+board3volt+"\"}";
  
  webSocket.broadcastTXT(JSONtxt1);
/*
  JSONtxt2 = "{\"board2\":\""+board2volt+"\"}";
  webSocket.broadcastTXT(JSONtxt2); 

  JSONtxt3 = "{\"board3\":\""+board3volt+"\"}";
  webSocket.broadcastTXT(JSONtxt3);   
  */
  Serial.print("board 1 :");
  Serial.print(board1_volt);
  Serial.print("\t");
  Serial.print("board 2 :");
  Serial.print(board2_volt);
  Serial.print("\t");
  Serial.print("board 3 :");
  Serial.print(board3_volt);
  Serial.println();
}
