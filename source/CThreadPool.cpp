#include "CThreadPool.h"
CThreadPool* CThreadPool::ptr = nullptr;
CThreadPool* CThreadPool::instance(unsigned int poolSize)
{
    if(ptr==nullptr)
    {
        ptr = new CThreadPool(poolSize);

    }
    return ptr;
}

CThreadPool::CThreadPool(int size):poolCount(size){
    this->busyNum = 0;
    this->isRunning = false;
}
CThreadPool::~CThreadPool()
{
    /* destroy all thread */

}

void CThreadPool::work()
{
    std::cout << "begin work thread:[" << std::this_thread::get_id() << "]" << std::endl;
    while(isRunning)
    {
        Task task;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if(!taskQueue.empty())
            {
                task = taskQueue.front();
                taskQueue.pop();
            }
            else if(isRunning && taskQueue.empty())
                condition_.wait(lock);
        }
        if(task)
        {
            task();
        }
    }
}

int CThreadPool::addTask(const Task& task)
{
    if(isRunning)
    {
        std::unique_lock<std::mutex> unlock(mutex_);
        this->taskQueue.push(task);
        condition_.notify_one();
    }
}

int CThreadPool::start()
{
    for(int i=0;i<poolCount;i++)
    {
        /* 成员函数做线程入口的传入方法 */
        this->threadPool.push_back(new std::thread(std::mem_fun(&CThreadPool::work),this));
        this->stateMap[i] = false;
    }
    isRunning = true;
}
int CThreadPool::stop()
{
    for(auto t:threadPool)
    {
        if(t->joinable())
            t->join();
    }
    isRunning = false;
}