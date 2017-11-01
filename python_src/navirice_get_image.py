# Echo client program
import socket
import time

class Image:
    def __init__(self, width, height, channels, type_, data, data_size):
        self.width = width
        self.height = height
        self.channels = channels
        self.type_ = type_
        self.data = data
        self.data_size = data_size

def navirice_get_image(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    data = s.recv(1024)
    b_size = 100000
    while(True):
        t = s.recv(b_size)
        if not t:
            break
        data += t
    s.close()
    print(len(data))


HOST = 'localhost'  # The remote host
PORT = 29000        # The same port as used by the server

while(1):
    time.sleep(0.01)
    navirice_get_image(HOST, PORT)


