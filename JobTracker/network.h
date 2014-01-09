#ifndef NETWORK_H
#define NETWORK_H

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
#include "../my_unp.h"

#include "command.h"

class NetWork
{
private:
    int listenfd;
    short int serv_port;
public:
    NetWork();
    ~NetWork();
    void init();
    void daemon();

};



#endif
