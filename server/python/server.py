import socket as Socket
import threading
from flask import Flask, jsonify, render_template_string

app = Flask(__name__)

client_socket = None
client_lock = threading.Lock()

HTML_TEMPLATE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
    <title>Device Control</title>
</head>
<body>
    <h1>Device Control Panel</h1>
    <button onclick="sendCommand('on')">Turn ON</button>
    <button onclick="sendCommand('off')">Turn OFF</button>
    <p id="response">{{ message }}</p>

    <script>
        async function sendCommand(cmd) {
            const response = await fetch(`/${cmd}`);
            const data = await response.text();
            document.open();
            document.write(data);
            document.close();
        }
    </script>
</body>
</html>
"""

@app.route('/')
def home():
    return render_template_string(HTML_TEMPLATE, message="")

@app.route('/on')
def turn_on():
    with client_lock:
        if client_socket:
            try:
                client_socket.sendall(b"ON\n")
                return render_template_string(HTML_TEMPLATE, message="Sent ON to client.")
            except Exception as e:
                return render_template_string(HTML_TEMPLATE, message=f"Failed to send ON: {str(e)}")
        else:
            return render_template_string(HTML_TEMPLATE, message="No client connected.")

@app.route('/off')
def turn_off():
    with client_lock:
        if client_socket:
            try:
                client_socket.sendall(b"OFF\n")
                return render_template_string(HTML_TEMPLATE, message="Sent OFF to client.")
            except Exception as e:
                return render_template_string(HTML_TEMPLATE, message=f"Failed to send OFF: {str(e)}")
        else:
            return render_template_string(HTML_TEMPLATE, message="No client connected.")

def run_flask():
    app.run(host='0.0.0.0', port=5000)

def run_tcp_server():
    global client_socket

    port: int = 8080
    host: str = Socket.gethostname()

    try:
        server_socket = Socket.socket(Socket.AF_INET, Socket.SOCK_STREAM)
        server_socket.bind((host, port))
        server_socket.listen(1)
        print(f"[TCP] TCP Server listening on {host}:{port}")

        client_socket, client_address = server_socket.accept()
        print(f"[TCP] Connection from {client_address} has been established!")
        client_socket.sendall(b"[TCP] Welcome to the server!\n")

        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            print(f"[TCP] Received from client: {data.decode().strip()}")

        client_socket.close()
        server_socket.close()
        print("[TCP] Client disconnected.")

    except Socket.error as err:
        print("[TCP] Socket error:", err)

if __name__ == "__main__":
    flask_thread = threading.Thread(target=run_flask, daemon=True)
    flask_thread.start()

    run_tcp_server()
