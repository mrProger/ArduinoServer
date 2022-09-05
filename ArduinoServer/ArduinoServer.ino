#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 11
#define TFT_DC 8
#define TFT_MOSI 38
#define TFT_SCLK 40
#define TFT_RST 9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 100, 20);
IPAddress myDns(192, 168, 100, 1);
EthernetServer server(80);
IPAddress currIp;

void EthernetInit() {
  if (Ethernet.begin(mac) == 0) {
    Serial.println("ERROR > Failed dhcp");

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("ERROR > Ethernet shield not found");  
    }
    else {
      Serial.println("INFO > Ethernet shiled founded");
    }

    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("ERROR > Ethernet cable is not connected");  
    }
    else {
      Serial.println("INFO > Ethernet cable is connected");
    }

    Ethernet.begin(mac, ip, myDns);
  }
  else {
    drawtext("IP:", ST7735_WHITE, 0, 0);
    drawtext(ipToString(Ethernet.localIP()), ST7735_WHITE, 18, 0);
  }  
}

const char* ipToString(IPAddress ip) {
  static char resIp[16];
  sprintf(resIp, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return resIp;
}

void drawtext(const char* text, uint16_t color, int16_t x, int16_t y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void DisplayInit() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);  
}

void setup() {
  Serial.begin(9600);
  DisplayInit();
  EthernetInit();
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean ok = true;
 
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
 
        if (c == '\n' && ok) {
 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5"); // время обновления страницы 
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><meta charset='UTF-8'>");
 
          client.println("<h1>Привет МИР!!!</h1>");
 
          client.println("</html>");
 
          break;
        }
        if (c == '\n'){ok = true;}else if(c != '\r'){ok = false;}
      }
    }
 
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}
