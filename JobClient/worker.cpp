#include "worker.h"

void mergeCommand(int argc, char **argv, char *buf)
{
    if(argc == 1)
        err_quit("Usage: worker <sendbuf>\n");

    for(int i = 1; i < argc; ++i)
        cout<<argv[i]<<endl;
 
    size_t nlen = 0;

    char strMerge[MAXLINE] = {0};
    cout<<"test1"<<endl;
    for(int i = 1; i < argc; ++i)
    {
        nlen += strlen(argv[i]);
        if(nlen >= MAXLINE)
            err_quit("failed, the command can not more than MAXLINE\n");
        strcat(strMerge, argv[i]);
        if(i != argc)
        {
            strcat(strMerge, " ");
            nlen += 1;
        }
    cout<<"test2"<<endl;
    }
    cout<<"test3"<<endl;

    strcpy(buf, strMerge);
    cout<<"the command is:"<<endl<<buf<<endl;
}
int main(int argc, char **argv)
{
    char strbuf[MAXLINE];
    mergeCommand(argc, argv, strbuf);

    NetworkClient network;
    cout<<"start to connect..."<<endl;
    if(network.connect() < 0)
        err_quit("connect failed..\n");
    else
        cout<<"connect succesful."<<endl;

    network.send(strbuf);


    return 0;
}
