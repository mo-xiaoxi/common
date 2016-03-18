# -*- coding: UTF-8 -*-

import socket, time
from sys import exit

# 服务器地址，初始化socket
ser_address = ('localhost', 10218)
cli_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 设置超时
cli_socket.settimeout(5)

# 向服务器发送消息，并判断接收时是否超时，若超时则重发
while 1:
    cli_socket.sendto('startCam', ser_address)
    try:
        message, address = cli_socket.recvfrom(2048)
        if message == 'startRcv':
            print message
            break
    except socket.timeout:
        print "eafes"
        continue

cli_socket.recvfrom(65536)

