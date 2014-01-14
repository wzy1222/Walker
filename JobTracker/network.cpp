#include "network.h"
#include "../NetTransfer/NetTransfer.h"

NetWork::NetWork()
{
    listenfd = 0;
    serv_port = 19001;
}
NetWork::~NetWork()
{
}
void NetWork::init()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd)
        err_quit("NetWork::init(): failed in socket()\n");
    struct sockaddr_in serv_addr;
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(serv_port);
    if(-1 == bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(sockaddr_in)))
       err_quit("NetWork::init(): failed in bind()\n");
    if(-1 == listen(listenfd, 5))
       err_quit("NetWork::init(): failed in listen()\n");
    cout<<"listen ok.."<<endl;
}
void NetWork::daemon()
{
    struct sockaddr_in addr_client;
    socklen_t len_client = sizeof(sockaddr_in);
    int connfd;
    pid_t childpid;
    while(true)
    {
        connfd = accept(listenfd, (struct sockaddr *)&addr_client, &len_client);
        if(-1 == connfd)
            err_quit("NetWork::daemon:failed in accept()");

        if((childpid = fork()) > 0) //parent
        {
            close(connfd);
        }
        else    //child
        {
            close(listenfd);
            //Command cmd(connfd);
            //cmd.recvOnce();

            cout<<"connfd  = "<<connfd<<endl;
            NetTransfer nt(connfd);
            nt.Recv();



            close(connfd);
            exit(0);
        }
    }
}
