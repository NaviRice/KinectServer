# Echo client program
import socket
import time
import os

os.system("protoc -I=../proto --python_out=. ../proto/navirice_image.proto")

import navirice_image_pb2

class Image:
    def __init__(self, width, height, channels, type_, data, data_size):
        self.width = width
        self.height = height
        self.channels = channels
        self.type_ = type_
        self.data = data
        self.data_size = data_size

def navirice_get_image(host, port, last_count):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    count_msg = s.recv(1024);
    count_obj = navirice_image_pb2.ProtoImageCount()
    count_obj.ParseFromString(count_msg)
    count = count_obj.count
    if(last_count >= count):
        s.close()
        return None, last_count;

    continue_msg = navirice_image_pb2.ProtoAcknowledge()
    continue_msg.state = navirice_image_pb2.ProtoAcknowledge.CONTINUE
    bytes_sent = s.send(continue_msg.SerializeToString())

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
    return img_set, count;


HOST = '127.0.0.1'  # The remote host
PORT = 29000        # The same port as used by the server

last_count = 0
while(1):
    time.sleep(0.01)
    img_set, last_count = navirice_get_image(HOST, PORT, last_count)
    if(img_set != None):
        print("IMG#: ", img_set.count)
        print("RGB width: ", img_set.RGB.width)
        print("RGB height: ", img_set.RGB.height)
        print("RGB channels: ", img_set.RGB.channels)

