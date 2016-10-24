#!/usr/bin/env node

// https://github.com/websockets/ws

subscriptions = {}

var WebSocketServer = require('ws').Server;
wss = new WebSocketServer({ port: 8080 , path: '/abc' });

wss.on('connection', function connection(ws) {
    ws.on('message', function incoming(message) {
        console.log('received: %s', message);
        elements = message.split(' ');
        command = elements[0]
        switch (command) {
            case 'subscribe':
                if (elements.length != 2) {
                    ws.send('Error: 1 argument needed');
                } else {
                    topic = elements[1];
                    if (!(topic in subscriptions)) subscriptions[topic] = [];
                    if (subscriptions[topic].indexOf(ws) == -1) subscriptions[topic].push(ws);
                }
                break;
            case 'unsubscribe':
                if (elements.length != 2) {
                    ws.send('Error: 1 argument needed');
                } else {
                    topic = elements[1]
                    if (topic in subscriptions) subscriptions[topic] = [];
                    subscriptions = subscriptions.filter(function(element) { return element!=wc});
                    if (subscriptions[topic].indexOf(ws) == -1) subscriptions[topic].push(ws);
                }
                break;
            case 'list':
                var result = []
                for (var topic in subscriptions) {
                    console.log(topic);
                    console.log(subscriptions[topic]);
                    console.log(subscriptions[topic][0] === ws)
                    subscribers = subscriptions[topic].map(function(i) {return subscriptions[topic][i]})
                    console.log(subscribers)
//                    if (ws in subscribers) {
                    if (subscriptions[topic].indexOf(ws) != -1) {
                        console.log(result);
                        result.push(topic);
                        console.log(result);
                    }
                }
                ws.send(JSON.stringify(result));
                break;
            case 'publish':
                if (elements.length < 3) {
                    ws.send('Error: 2+ arguments needed');
                } else {
                    var topic = elements[1];
                    var message = elements.slice(2, -1).join(' ');
                    if (topic in subscriptions) {
                        for (var i in subscriptions[topic]) subscriptions[topic][i].send(message);
                    }
                }
                break;
            default:
                ws.send('Error: Unrecognized command "'+command+'"');
        }
    });
    ws.on('close', function (code, message) {
          for (var topic in subscriptions) {
            var i = subscriptions[topic].indexOf(ws);
            if (i!=-1) subscriptions[topic].splice(i, 1);
          }
    });
    
    ws.send('something');
});

