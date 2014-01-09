#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "../my_unp.h"
using namespace std;

class NetworkClient
{
private:
    int connfd;
    char serv_ip[16];
    short int serv_port;
public:
    NetworkClient();
    ~NetworkClient();

    int connect();
    void send(char *strbuf);    
};



#endif
