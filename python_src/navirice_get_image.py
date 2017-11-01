# Echo client program
import socket
import time

import navirice_image_pb2

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
    data = "".encode()
    b_size = 10000000
    while(True):
        t = s.recv(b_size)
        if not t:
            break
        data += t
    s.close()
    print(len(data))
    img_set = navirice_image_pb2.ProtoImageSet()
    img_set.ParseFromString(data)
    return img_set


HOST = 'localhost'  # The remote host
PORT = 29000        # The same port as used by the server

while(1):
    time.sleep(0.01)
    img_set = navirice_get_image(HOST, PORT)
    print("IMG#: ", img_set.count)
    print("RGB width: ", img_set.RGB.width)
    print("RGB height: ", img_set.RGB.height)
    print("RGB channels: ", img_set.RGB.channels)

