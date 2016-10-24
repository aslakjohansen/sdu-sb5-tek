#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include<signal.h>
#include "shared.h"

void signal_handler(int signo) {}

int main (int argc, char* argv) {
    // register signal handler
    if (signal(SIGPIPE, signal_handler) == SIG_ERR) die("Error registering signal handler");
    
    // create
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1) die("Error creating socket");
    
    // bind
    struct sockaddr* addr = get_local_addr(SERVER_PORT);
    if (bind(fd, addr, sizeof(*addr)) < 0) die("Error binding socket");
    
    // listen
    if (listen(fd, 1) != 0) die("Error listening");
    
    while (1) {
        // accept
        struct sockaddr peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);
        int connection_fd = accept(fd, &peer_addr, &peer_addr_len);
        if (connection_fd == -1) die("Error accepting");
        
        // read
        time_t t;
        if (recv(connection_fd, &t, sizeof(t), 0) == -1) die("Error recieving");
        
        // send one tick every second until client disconnects
        do {
            t++;
            sleep(1);
        } while (send(connection_fd, &t, sizeof(t), 0) == sizeof(t));
    }
    
    return 0;
}

