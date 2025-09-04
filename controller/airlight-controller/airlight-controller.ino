#include <SoftwareSerial.h>

#define esp8266_RX 10
#define esp8266_TX 11

SoftwareSerial esp8266(esp8266_RX, esp8266_TX);

String wifiName;
String wifiPass;
String hostName;
int port = 8000;

class WiFiModule {
  private:
    SoftwareSerial& esp8266;

  public:
    WiFiModule(SoftwareSerial& serial) : esp8266(serial) {}

    void begin(long baudRate) {
      esp8266.begin(baudRate);
    }

    bool sendCommand(String command, int waitTime) {
      esp8266.println(command);
      delay(waitTime);

      String response = esp8266.readString();
      Serial.println(response);

      if (response.indexOf("OK") != -1) {
        Serial.println("[+] Command Successful: " + command);
        return true;
      } else {
        Serial.println("[-] Command Failed: " + command);
        return false;
      }
    }

    bool connectWiFi(String ssid, String password) {
      String connectCommand = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
      return sendCommand(connectCommand, 6000);
    }

    bool connectSocket(String host, int port) {
      String connectHost = "AT+CIPSTART=\"TCP\",\"" + host + "\"," + port;
      return sendCommand(connectHost, 4000);
    }
};

WiFiModule wifiModule(esp8266);

void setup() {
  Serial.begin(9600);
  Serial.println("[+] Serial Setup Complete...");

  wifiModule.begin(9600);

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

  Serial.println("[*] Sending reset command...");
  wifiModule.sendCommand("AT+RST", 2000);

  Serial.println("[*] Setting to Station Mode...");
  wifiModule.sendCommand("AT+CWMODE=1", 1000);

  Serial.println("[*] Sending Wi-Fi Connect Command...");
  bool wifi_connect_response = wifiModule.connectWiFi(wifiName, wifiPass);

  if (wifi_connect_response) {
    Serial.println("[+] Wi-Fi Connected!");
  } else {
    Serial.println("[-] Wi-Fi Connection Failed!");
  }

  Serial.println("Enter your Hostname or IP:");
  while (hostName.length() == 0) {
    if (Serial.available()) {
      hostName = Serial.readStringUntil('\n');
      hostName.trim();
    }
  }

  Serial.println("[*] Sending Socket Connect Command...");
  bool socket_connect_response = wifiModule.connectSocket(hostName, port);

  if (socket_connect_response) {
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
