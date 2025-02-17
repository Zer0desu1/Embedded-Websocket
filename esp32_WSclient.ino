#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "";
const char* password = "";


WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED: {
            Serial.printf("[%u] Bağlantı kesildi!\n", num);
            break;
        }
            
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Bağlantı sağlandı - %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
            break;
        }
            
        case WStype_TEXT: {
            Serial.printf("[%u] Gelen metin: %s\n", num, payload);
            String message = String((char*)payload);
            
           
            if(message == "ON") {
                webSocket.sendTXT(num, "LED açıldı");
                Serial.println("LED açıldı");
            }
            else if(message == "OFF") {
                webSocket.sendTXT(num, "LED kapandı");
                Serial.println("LED kapandı");
            }
            break;
        }
            
        case WStype_BIN: {
            Serial.printf("[%u] Binary mesaj alındı, uzunluk: %u\n", num, length);
            break;
        }
            
        case WStype_ERROR: {
            Serial.printf("[%u] Hata oluştu\n", num);
            break;
        }
            
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
        default: {
            break;
        }
    }
}

void setup() {
    Serial.begin(115200);
    

    WiFi.begin(ssid, password);
    Serial.println("WiFi ağına bağlanılıyor");
    
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi bağlantısı başarılı");
    Serial.print("IP adresi: ");
    Serial.println(WiFi.localIP());
    
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("WebSocket sunucusu başlatıldı");
}

void loop() {
    webSocket.loop();
}
