import json
import os
import socket
from contextlib import contextmanager

TCP_IP = 'localhost'
TCP_PORT = 7777
BUFFER_SIZE = 1024


@contextmanager
def socketcontext(*args, **kwargs):
    s = socket.socket(*args, **kwargs)
    try:
        yield s
    finally:
        s.close()


with socketcontext(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((TCP_IP, TCP_PORT))

    request = """<credentials><login>John Doe</login>
                 <password>@12345</password></credentials>"""
    sock.send(request.encode())
    response = sock.recv(BUFFER_SIZE)
    print(response.decode())

    request = """<report><payer>1</payer><tax>Corporate Income Tax</tax>
                <amount>25000</amount><year>2020</year></report>"""
    sock.send(request.encode())
    response = sock.recv(BUFFER_SIZE)
    print(response.decode())
