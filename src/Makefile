TARGETS = \
	socket_client \
	socket_server \

CARGS = -g



all: ${TARGETS}

clean:
	touch ${TARGETS}
	rm    ${TARGETS}

mrproper: clean
	touch dummy~
	rm        *~

deps:
	npm install http
	npm install httpdispatcher
	npm install ws
	#websocket



socket_client: socket_client.c shared.c
	gcc ${CARGS} socket_client.c shared.c -o socket_client

socket_server: socket_server.c shared.c
	gcc ${CARGS} socket_server.c shared.c -o socket_server

