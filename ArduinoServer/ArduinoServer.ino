#include <SPI.h>
#include <Ethernet.h>
#include "src/Display/Display.h"

#define TFT_CS 11
#define TFT_DC 8
#define TFT_MOSI 38
#define TFT_SCLK 40
#define TFT_RST 9

Display* display = new Display(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
char* buffer;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 100, 20);
IPAddress myDns(192, 168, 100, 1);
EthernetServer server(80);
IPAddress currIp;

const char* CombineString(const char* firstStr, const char* secondStr, const char* delimeter) {
  buffer = calloc(strlen(firstStr) + strlen(secondStr) + strlen(delimeter) + 1, 1);
  strcat(buffer, firstStr);
  strcat(buffer, delimeter);
  strcat(buffer, secondStr);
  return buffer;
}

const char* ipToString(IPAddress ip) {
  static char resIp[16];
  sprintf(resIp, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return resIp;
}

void EthernetInit() {
    if (Ethernet.begin(mac) == 0) {
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
            display->WriteLine("IP: Error");
            display->WriteLine("Status: Error, Ethernet shield not found");
            return;
        }

        if (Ethernet.linkStatus() == LinkOFF) {
            display->WriteLine("IP: Error");
            display->WriteLine("Status: Error, Ethernet cable is not connected");
            return;
        }

        Ethernet.begin(mac, ip, myDns);
        const char* ipStr = CombineString("IP: ", ipToString(ip), "");
        display->WriteLine(ipStr);
        free(buffer);
        display->WriteLine("Status: Working");
    }
    else {
        const char* ipStr = CombineString("IP: ", ipToString(Ethernet.localIP()), "");
        display->WriteLine(ipStr);
        free(buffer);
        display->WriteLine("Status: Working");
    }
}

void setup() {
  Serial.begin(9600);
  display->Init();
  display->Clear();
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
          client.println("Refresh: 5"); // ?????????? ???????????????????? ???????????????? 
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><meta charset='UTF-8'>");
 
          client.println("<h1>???????????? ??????!!!</h1>");
 
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
