#pragma once
#include <unistd.h>
#include <iostream>
#include <string>
#include "CThreadPool.h"
/* socket headerfile */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

const int maxConnection = 10;

class Server_Bio{
public:
    Server_Bio(std::string ip,unsigned int port);
    Server_Bio(const Server_Bio& S) = delete;
    void polling();
    ~Server_Bio();
private:
    std::string ip;
    unsigned int port;
    int listen_fd;
    CThreadPool* poolPtr;
};