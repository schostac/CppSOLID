import socket
import json

TCP_IP = 'localhost'
TCP_PORT = 8000
BUFFER_SIZE = 1024
MESSAGE = json.dumps({
    'payer': 100, 
    'tax': 'Corporate Income Tax',
    'amount': 25000,
    'year': 2020
})

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((TCP_IP, TCP_PORT))
    s.send(MESSAGE.encode())
    data = s.recv(BUFFER_SIZE)
    print('Received data:', data.decode())
