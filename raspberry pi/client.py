#!/usr/bin/python
# -*- coding: utf-8 -*-
#__Author__ = moxiaoxi
#___name___ = task2 as client(Alice)

import socket,hashlib
import time
import struct
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
port = 23457
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
'''
向服务器发送消息，并判断接收时是否超时，若超时则重发
打包一个序列值，保证每个包的唯一性，同时也可以防止由于
传输时间过长，导致client假阳性误报server没有接受当前
包，重传问题
'''
datas = ['m1','m2','m3','end']

for i  in range(len(datas)):
    if not datas[i]:
        print "data error"
        break
    tmp=struct.pack("<3si",datas[i],i)
    Sock.sendto(tmp,ADDR)
    print 'data',tmp,'sended ,destination',ADDR
    md=md5(tmp)
    print md
    while True:
        try:
            message,address = Sock.recvfrom(bufsiz)
            if message == md:
                print 'ack successful ! send next packet'
                break
            else:
                print "ack data error,send again"
                Sock.sendto(tmp,ADDR)
        except socket.timeout:
            print "timeout,send again"
            Sock.sendto(tmp,ADDR)
               
                

Sock.close()