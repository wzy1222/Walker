/*
 * daemon process,wait for a new job
 */

#include "JobDaemon.h"
#include "../Common/mylog.h"


int main(int argc,char **argv)
{
    MyLog::Init();
    NetWork network;
    network.init();
    network.daemon();


    MyLog::Exit();
    return 0;
}
