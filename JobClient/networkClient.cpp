#include "networkClient.h"

NetworkClient::NetworkClient()
{
    connfd = 0;
    serv_port = 19001;
    strcpy(serv_ip, "127.0.0.1");
}
NetworkClient::~NetworkClient()
{
}

int NetworkClient::connect()
{
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == connfd)
        err_quit("NetworkClient::connect: failed in socket()\n");
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(sockaddr_in)); 
    serv_addr.sin_family = AF_INET;
    inet_aton(serv_ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(serv_port);
    socklen_t len = sizeof(sockaddr_in);

    // 3 kinds of errors: timeout unreachable refuse.
    if(-1 == ::connect(connfd, (struct sockaddr*)&serv_addr, len))
    {
        cout<<"connect failed"<<endl;
        return -1;
    }

    return 1;
}
void NetworkClient::send(char *strbuf)
{
    size_t len = strlen(strbuf);
    ssize_t n;
    cout<<"NetworkClient: start to write..."<<endl;
    n = writen(connfd, strbuf, len);
    if(n == len)
        cout<<"NetworkClient: write succesful."<<endl;
    else
        cout<<"NetworkClient: just "<<n<<" bytes wirted,"<<len - n<<" bytes failed"<<endl;
}
