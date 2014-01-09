#ifndef COMMAND_H
#define COMMAND_H

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

using namespace std;
class Command
{
private:
    int connfd;
public:
    Command(int fd);
    ~Command();

    //receive one command,then interupt the connection.
    void recvOnce();
};






#endif
