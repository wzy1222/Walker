#include "command.h"

Command::Command(int fd)
{
    connfd = fd;
}
Command::~Command()
{
}

void Command::recvOnce()
{
    //read one command,which end of '$'
    ssize_t nread;
    ssize_t n = 0;
    char buf[MAXLINE + 1];
    char *ptr = buf;

    while((nread = read(connfd, ptr, MAXLINE)) > 0)
    {
        n += nread;
        if(*(ptr + nread - 1) != '$')
        {
            ptr += nread;
            continue;
        }
        break;
    }
    if(nread < 0)
        err_quit("Command::recvOnce: failed in read()\n");

    buf[n]='\0';
    cout<<"recvOnce: "<<buf<<endl;
}          

