#!/usr/bin/python
# -*- coding: utf-8 -*-
#__Author__ = moxiaoxi
#___name___ = task1 as client(Alice)

import socket,hashlib
import time
from  sys import exit 
def md5(str):
    import hashlib
    import types
    if type(str) is types.StringType:
        m = hashlib.md5()   
        m.update(str)
        return m.hexdigest()
    else:
        return ''

    
host = 'localhost'  
port = 23456
bufsiz = 1024
ADDR = (host,port)
time = 5

#初始化socket
try:
    Sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error, msg:
    print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
    sys.exit();

# 设置超时
Sock.settimeout(time)

# 向服务器发送消息，并判断接收时是否超时，若超时则重发

datas = ['m1','m2','m3','end']
for data  in datas:
    if not data:
        print "data error"
        break
    Sock.sendto(data,ADDR)
    print 'data',data,'sended ,destination',ADDR
    md=md5('data')
    print md
    while True:
        try:
            data,address = Sock.recvfrom(bufsiz)
            if cmp( data , md ):
                print 'ack successful ! send next packet'
                break
            else:
                print "ack data error,send again"
                Sock.sendto(data,ADDR)
        except socket.timeout:
            print "timeout,send again"
            Sock.sendto(data,ADDR)
               
                

Sock.close()