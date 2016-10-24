#!/usr/bin/env python3.5

import sys
from shared import *
import socket

# fetch path from command line arguments
path = sys.argv[1]

# setup client socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((INTERFACE, CLIENT_PORT))
#INTERFACE = '172.217.17.46'
#CLIENT_PORT = 80
# connect to server
s.connect((INTERFACE, SERVER_PORT))

# send request
s.send(str.encode('GET %s HTTP/1.1%s' % (path, LINE_ENDING)))
s.send(str.encode('Host: %s%s' % (INTERFACE, LINE_ENDING)))
s.send(str.encode('%s' % LINE_ENDING))

# receive response
header = recv_line(s)
proto, machine, human = header.split(' ')
args = recv_args(s)
content = s.recv(int(args['Content-Length'])).decode()
print(content)

