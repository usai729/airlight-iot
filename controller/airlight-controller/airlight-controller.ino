#include <SoftwareSerial.h>

#define esp8266_RX 10
#define esp8266_TX 11

SoftwareSerial esp8266(esp8266_RX, esp8266_TX);

String wifiName;
String wifiPass;

String hostName;
int port = 8000;

void setup() {
  Serial.begin(9600);
  Serial.println("[+] Serial Setup Complete...");

  esp8266.begin(115200);

  Serial.println("Enter your Wi-Fi name (SSID):");
  while (wifiName.length() == 0) {
    if (Serial.available()) {
      wifiName = Serial.readStringUntil('\n');
      wifiName.trim();
    }
  }

  Serial.println("Enter your Wi-Fi password:");
  while (wifiPass.length() == 0) {
    if (Serial.available()) {
      wifiPass = Serial.readStringUntil('\n');
      wifiPass.trim();
    }
  }

  esp8266.println("AT+RST");
  delay(2000);
  Serial.println("[+] Sent reset command...");

  esp8266.println("AT+CWMODE=1");
  delay(1000);
  Serial.println("[+] Set to Station Mode...");

  String connectWiFi = "AT+CWJAP=\"" + wifiName + "\",\"" + wifiPass + "\"";
  esp8266.println(connectWiFi);
  delay(6000);
  Serial.println("[*] Sent Wi-Fi Connect Command...");

  if (esp8266.find("OK")) {
    Serial.println("[+] Wi-Fi Connected!");
  } else {
    Serial.println("[-] Wi-Fi Connection Failed!");
  }

  // Get Hostname/IP
  Serial.println("Enter your Hostname or IP:");
  while (hostName.length() == 0) {
    if (Serial.available()) {
      hostName = Serial.readStringUntil('\n');
      hostName.trim();
    }
  }

  String connectHost = "AT+CIPSTART=\"TCP\",\"" + hostName + "\"," + port;
  esp8266.println(connectHost);
  delay(4000);
  Serial.println("[*] Sent Socket Connect Command...");

  if (esp8266.find("OK")) {
    Serial.println("[+] Socket Connection Established!");
  } else {
    Serial.println("[-] Socket Connection Failed!");
  }
}

void loop() {
  if (esp8266.available()) {
    Serial.write(esp8266.read()); 
  }
}
