#include "CTask.h"
tcp_Task::tcp_Task(int fd,addr sin):fd(fd),clientSin(sin){
    connectFlag = true;
}
tcp_Task::tcp_Task(const tcp_Task& obj):fd(obj.fd),clientSin(obj.clientSin){}
tcp_Task::~tcp_Task(){
    close(fd);
}
void tcp_Task::operator()()
{
    std::cout<<"in the tcp_task\r\n";
    std::cout <<"client ip : "<<clientSin.sin_addr.s_addr<<std::endl;
    /* read and write*/
    while(connectFlag)
    {
        
    }
}