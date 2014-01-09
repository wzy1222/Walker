/*
 * daemon process,wait for a new job
 */

#include "JobDaemon.h"


int main(int argc,char **argv)
{
    NetWork network;
    network.init();
    network.daemon();
    return 0;
}
