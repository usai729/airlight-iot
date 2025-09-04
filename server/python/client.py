import socket as Socket

client_socket: Socket.socket = None
port: int = 8000
host: str = Socket.gethostname()

try:
    client_socket = Socket.socket(Socket.AF_INET, Socket.SOCK_STREAM)
    client_socket.connect((host, port))
    print(f"Connected to server at {host}:{port}")

    while True:
        response = client_socket.recv(1024)
        if not response:
            print("Disconnected from server.")
            break
        print("Message from server:", response.decode("utf-8"))

    client_socket.close()

except Socket.error as err:
    print("Could not connect to server:", err)
