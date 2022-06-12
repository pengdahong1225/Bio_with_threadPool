#include "Server_BIO.h"
Server_Bio::Server_Bio(std::string ip,unsigned int port):ip(ip),port(port)
{
    this->listen_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(listen_fd == -1)
    {
        printf("socket() error\r\n");
        exit(0);
    }
    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_port = htons(port);
    if(bind(listen_fd,(sockaddr*)&sin,sizeof(sin)) == -1)
    {
        printf("bind() error\r\n");
        exit(0);
    }
    if(listen(listen_fd,maxConnection) == -1)
    {
        printf("listen() error\r\n");
        exit(0);
    }
    printf("listen status : ok\r\n");
    poolPtr = nullptr;
}

Server_Bio::~Server_Bio()
{
    close(listen_fd);
}

void Server_Bio::polling()
{
    if(poolPtr == nullptr)
    {
        poolPtr = CThreadPool::instance(maxConnection);
    }
    poolPtr->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    while(true)
    {
        printf("waiting connection\r\n");
        struct sockaddr_in remoteAddr{};
        socklen_t* len;
        int fd = accept(this->listen_fd,(sockaddr*)&remoteAddr,len);
        /* fd to taskfunction */
        poolPtr->addTask(tcp_Task(fd,remoteAddr));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}