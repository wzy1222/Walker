#include "datanodeNet.h"

DatanodeNet::DatanodeNet()
{
    listenfd = 0;
    serv_port = 19002;
}
DatanodeNet::~DatanodeNet()
{
}
void DatanodeNet::init()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd)
	{
        LOG__(LOGID_I, "DatanodeNet::init(): failed in socket()\n");
		exit(1);
	}
    struct sockaddr_in serv_addr;
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(serv_port);
    if(-1 == bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(sockaddr_in)))
	{
       LOG__(LOGID_I, "DatanodeNet::init(): failed in bind()\n");
	   exit(1);
	}
    if(-1 == listen(listenfd, 5))
	{
       LOG__(LOGID_I, "DatanodeNet::init(): failed in listen()\n");
	   exit(1);
	}
	LOG__(LOGID_I, "listen success");
//    cout<<"listen ok.."<<endl;
}
void DatanodeNet::daemon()
{
    struct sockaddr_in addr_client;
    socklen_t len_client = sizeof(sockaddr_in);
    int connfd;
    pid_t childpid;
    while(true)
    {
        connfd = accept(listenfd, (struct sockaddr *)&addr_client, &len_client);
        if(-1 == connfd)
		{
            LOG__(LOGID_I, "DatanodeNet::daemon:failed in accept()");
			exit(1);
		}
        if((childpid = fork()) > 0) //parent
        {
            close(connfd);
        }
        else    //child
        {
            close(listenfd);
 //           Command cmd(connfd);
  //          cmd.recvOnce();
            close(connfd);
            exit(0);
        }
    }
}
