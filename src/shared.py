# https://www.jmarshall.com/easy/http/

LINE_ENDING = '\r\n'
INTERFACE = '0.0.0.0'
CLIENT_PORT = 8021
SERVER_PORT = 8012

def recv_line (s):
    last = ''
    line = ''
    while True:
        c = s.recv(1).decode()
        line += c
#        print('line = "%s"' % line)
        if last == '\r' and c=='\n':
            return line
        last = c

def recv_args (s):
    args = {}
    done = False
    while not done:
        line = recv_line(s)
        if line == LINE_ENDING:
#            recv_line(s)
            return args
        key, value = line.split(': ')
        args[key] = value

