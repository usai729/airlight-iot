# Arduino + ESP8266 Wi-Fi Socket Client

This project connects an **Arduino Uno** with an **ESP8266 Wi-Fi module** to a custom **Python TCP + Flask server**.

## 📡 How it Works

-   Arduino takes Wi-Fi credentials and server IP from the user via the Serial Monitor.
-   Connects the ESP8266 to Wi-Fi.
-   Opens a **TCP socket** connection to the server.
-   Sends and receives data between the Arduino and server.

## 💻 Server Side

A Flask-based web UI provides buttons to:

-   **Turn ON** a device
-   **Turn OFF** a device
-   **Exit** the connection

These commands are transmitted to the Arduino through the TCP socket.

## 🚀 Use Case

This setup can be used for **IoT projects** like controlling lights, appliances, or other hardware over the internet.

## Contributors

-   [Your Name](https://github.com/usai729)

---

Feel free to open an issue or create a pull request if you encounter any bugs or have suggestions for improvements!
