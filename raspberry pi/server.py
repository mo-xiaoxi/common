#!/usr/bin/env python
# -*- coding:utf-8 -*-
#__Author__ = moxiaoxi
#___name___ = task2 as server(Bob)


import socket,hashlib
import time
import struct
from threading import Thread
import traceback
import threading
def md5(str):
    import hashlib
    import types
    if type(str) is types.StringType:
        m = hashlib.md5()   
        m.update(str)
        return m.hexdigest()
    else:
        return ''

# 全局变量
is_ending = False
sequence = -1

'''
host为空表示bind可以绑定到所有有效地址上
port 必须要大于1024
bufsiz为缓冲区 我们设置为1K
'''
host = 'localhost'  
port = 23457
bufsiz = 1024
ADDR = (host,port)

# 初始化UDP socket
try:
    ser_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error, msg:
    print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]

ser_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
ser_socket.bind(ADDR)

# 接收线程类，用于接收客户端发送的消息
class UdpReceiver(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.thread_stop = False
                
    def run(self):
        while not self.thread_stop:
            # 声明全局变量，接收消息后更改  
            global is_ending
            global sequence
            try:
                message, cli_address = ser_socket.recvfrom(2048)
                print "receieving data :",message
            except:
                traceback.print_exc()
                continue
            print message,cli_address
            tmp,i=struct.unpack("<3si",message)
            if i == (sequence+1):
                sequence = i
                print "sequence sucessfully ,save it !"
                if tmp == "end":
                    is_ending = True
                md=md5(message)
                ser_socket.sendto(md, cli_address)
                print "send to ",cli_address,"data:",md                


    def stop(self):
        self.thread_stop = True



if __name__=='__main__':
    receiveThread = UdpReceiver()
    receiveThread.setDaemon(True)           # 该选项设置后使得主线程退出后子线程同时退出
    receiveThread.start()
    while True :
        if is_ending: 
            time.sleep(1) 
            break
        else:
            time.sleep(1)
  
    receiveThread.stop()
    print "receiveThread ended!"
    ser_socket.close()