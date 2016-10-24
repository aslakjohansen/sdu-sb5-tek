#!/usr/bin/env node

// https://github.com/websockets/ws

timers = {}

var WebSocketServer = require('ws').Server;
wss = new WebSocketServer({ port: 9999 , path: '/time' });

wss.on('connection', function connection(ws) {
    function timeout () {
        timers[ws]['time'] += 1;
        ws.send(timers[ws]['time'].toString());
        
        timer = setTimeout(timeout, 1000);
        timers[ws]['timer'] = timer;
    }
    
    ws.on('message', function incoming(message) {
        timer = setTimeout(timeout, 1000);
        timers[ws] = {'time': parseInt(message), 'timer': timer};
    });
    
    ws.on('close', function (code, message) {
        clearTimeout(timers[ws]['timer']);
        delete timers[ws];
    });
});

