# ESP8266 Wi-Fi + Socket Client with Arduino

This Arduino sketch allows an Arduino board to communicate with an **ESP8266 Wi-Fi module** over serial (AT commands).  
It connects the ESP8266 to Wi-Fi using user-provided credentials and establishes a **TCP socket connection** to a specified host and port.

---

## 🔧 Features

-   Serial input for Wi-Fi SSID and password.
-   Resets ESP8266 and configures it in **Station Mode** (`AT+CWMODE=1`).
-   Connects ESP8266 to the given Wi-Fi network (`AT+CWJAP`).
-   Prompts the user for a **hostname or IP address** and attempts to connect via TCP (`AT+CIPSTART`).
-   Logs success (`[+]`) or failure (`[-]`) messages to the Serial Monitor.
-   Displays data received from the ESP8266.

---

## 🛠 Hardware Requirements

-   Arduino Uno (or compatible board)
-   ESP8266 Wi-Fi Module
-   Logic Level Shifter (recommended, ESP8266 works on **3.3V**)
-   Jumper wires

---

## ⚡ Wiring

| Arduino Uno | ESP8266                     |
| ----------- | --------------------------- |
| 3.3V        | VCC                         |
| GND         | GND                         |
| D10 (RX)    | TX                          |
| D11 (TX)    | RX (via 3.3V level shifter) |

> ⚠️ Important: ESP8266 **cannot handle 5V directly** on RX. Use a voltage divider or level shifter.

---

## 💻 Software Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect Arduino to your PC via USB.
3. Copy the provided sketch into the Arduino IDE.
4. Select the correct **Board** and **COM Port**.
5. Upload the sketch.
6. Add esp8266 in preferences using http://arduino.esp8266.com/stable/package_esp8266com_index.json

---

## ▶️ Usage

1. Open **Serial Monitor** (set baud rate to `9600`).
2. Enter your **Wi-Fi SSID** → press Enter.
3. Enter your **Wi-Fi password** → press Enter.
4. Wait for `[+] Wi-Fi Connected!`.
5. Enter the **hostname/IP** of your server (e.g., `192.168.1.50`).
6. If successful, you’ll see messages received from the server
