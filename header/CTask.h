#pragma once
#include <unistd.h>
#include <iostream>
/* socket headerfile */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

/* base task */
/*class CTask{
public:
    virtual int run() = 0;
    virtual ~CTask();
};*/


class tcp_Task{
    using addr = struct sockaddr_in;
public:
    tcp_Task(int fd,addr sin);
    tcp_Task(const tcp_Task& obj);
    ~tcp_Task();
    void operator()();
    bool getFlag(){return connectFlag;}
private:
    int fd;
    bool connectFlag;
    addr clientSin{};
};
