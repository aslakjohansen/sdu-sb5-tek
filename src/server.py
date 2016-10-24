#!/usr/bin/env python3.5

from shared import *
import socket
from os.path import isdir
from os import listdir

# setup server socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((INTERFACE, SERVER_PORT))
s.listen(1)

# service loop
while True:
    # establish connection
    (client, address) = s.accept()
    
    try:
        # get header
        header = recv_line(client)
        verb, path, proto = header.split(' ')
        
        # get arguments
        args = recv_args(client)
        
        # produce contents
        if isdir(path):
            content = str(listdir(path))
        else:
            with open(path) as fo:
                content = ''.join(fo.readlines())
        
        # send content
        client.send(str.encode('HTTP/1.1 200 OK%s' % LINE_ENDING))
        client.send(str.encode('Connection: close%s' % LINE_ENDING))
        client.send(str.encode('Content-Length: %u%s' %(len(content), LINE_ENDING)))
        client.send(str.encode(LINE_ENDING))
        client.send(str.encode(content))
    except:
        client.send(str.encode('HTTP/1.1 500 Server Error%s' % LINE_ENDING))
        client.send(str.encode('Connection: close%s' % LINE_ENDING))
        
    
    # close connection
    client.close()

