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
//#include "../my_unp.h"

//#include "command.h"

//use yaolog
#include "../Common/yaolog.h"
#define LOGID_I "info"
#define LOGID_B "bin"
#define LOGID_FB "formatted_bin"
/*
 *init in main()
 *
 YAOLOG_INIT;   
 YAOLOG_SET_LOG_ATTR(LOGID_I, true, YaoUtil::LOGOUT_FLAG_STDOUT | YaoUtil::LOGOUT_FLAG_FILE, true, false, true, true, NULL);	
 YAOLOG_EXIT;   
*/

// LOG__(LOGID_I, "something");  //use

class DatanodeNet
{
private:
    int listenfd;
    short int serv_port;
public:
    DatanodeNet();
    ~DatanodeNet();
    void init();
    void daemon();

};



#endif