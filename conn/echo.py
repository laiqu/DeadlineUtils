#!/usr/bin/env python 

""" 
A simple echo server 
""" 

import socket 

host = 'localhost' 
port = 6112 
backlog = 5 
size = 1024 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host,port)) 
s.listen(backlog) 
while 1: 
    client, address = s.accept() 
    client.send("LOGIN\n")
    print "sent"
    data = client.recv(size) 
    print data
    client.send("PASS\n")
    data = client.recv(size) 
    print data
    client.send("OK\n")
    data = client.recv(size) 
    print data
    client.send("OK\n")
    client.close()
