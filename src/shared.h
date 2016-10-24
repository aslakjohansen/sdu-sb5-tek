#ifndef __SHARED_H
#define __SHARED_H

#define CLIENT_PORT (3335)
#define SERVER_PORT (3336)
#define SERVER_HOST ("localhost")

void die (char* message);

struct sockaddr* get_local_addr (int port);
struct sockaddr* get_remote_addr (char* host, int port);

#endif // __SHARED_H

