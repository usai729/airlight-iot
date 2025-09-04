# Device Control Web and TCP Server

This project sets up a basic Flask web interface to send commands to a device connected via a TCP socket. The web interface allows you to control the device by sending "ON", "OFF", and "EXIT" commands. The TCP server listens for incoming client connections and interacts with the device based on the received commands.

### Features:

-   **Flask Web Interface**: Allows the user to control the device via buttons.
-   **TCP Server**: Handles communication with the device over TCP.
-   **Multithreading**: Flask server and TCP server run concurrently using threads.

---

## Setup Instructions

1. **Clone the repository:**

    ```bash
    git clone https://github.com/usai729/airlight-iot
    cd <repository_directory>
    ```

2. **Install dependencies:**

    This project requires `Flask` to run the web server. Install the necessary Python packages using `pip`:

    ```bash
    pip install flask
    ```

3. **Run the application:**

    You can start the server by running the following command:

    ```bash
    python app.py
    ```

    This will start the Flask web server on `http://0.0.0.0:5000` and the TCP server on port `8000`.

4. **Access the web interface:**

    Open your browser and navigate to:

    ```
    http://localhost:5000
    ```

    You will see a web page with three buttons:

    - **Turn ON**: Sends an "ON" command to the connected TCP device.
    - **Turn OFF**: Sends an "OFF" command to the connected TCP device.
    - **Exit**: Closes the connection with the TCP server and shuts down the Flask app.

5. **TCP Server:**

    The TCP server listens on port `8000` for incoming client connections. Once a client connects, it will send a welcome message, and any command received will be printed to the console.

---

## How it Works

-   **Web Interface**:
    The Flask app serves a simple HTML interface with JavaScript to interact with the backend. When a user clicks one of the buttons, a command is sent to the backend server (Flask) via AJAX (`fetch`).
-   **TCP Server**:
    The TCP server listens for client connections on port `8000`. Upon receiving a connection, it sends a welcome message and waits for commands. The received commands are printed on the server-side, and the commands ("ON", "OFF", "EXIT") are communicated back to the device.

---

## Example of Commands Sent to Device:

-   **ON**: Sends the `ON` command to the device to power it on.
-   **OFF**: Sends the `OFF` command to the device to power it off.
-   **EXIT**: Closes the server connection and shuts down the Flask app.

---

## Important Notes

-   The `client_socket` variable is shared between the TCP server and the Flask server, ensuring that commands are sent to the correct client.
-   The Flask app runs on a separate thread to ensure that it doesn't block the TCP server from accepting connections.
-   If no client is connected, the web interface will inform the user that the command cannot be sent.

---

## Troubleshooting

-   **"No client connected" error**: This message will be shown if you try to send a command without an active TCP client connection. Make sure your device is connected before trying to control it.
-   **Socket Errors**: If you encounter socket errors, ensure that the TCP server is correctly set up, and the port `8000` is not in use by another process.

---
