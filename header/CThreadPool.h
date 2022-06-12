#pragma once
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "CTask.h"

class CThreadPool
{
    using Task = std::function<void()>;
public:
    static CThreadPool* instance(unsigned int poolSize);
    int start();
    int stop();
    int addTask(const Task& task);
private:
    CThreadPool(int size);
    ~CThreadPool();
    CThreadPool(const CThreadPool&)=delete;
    CThreadPool& operator=(const CThreadPool&)=delete;
    static CThreadPool* ptr;
    void work();
    
private:
    std::vector<std::thread*> threadPool;
    std::unordered_map<int,bool> stateMap;
    unsigned int poolCount;
    unsigned int busyNum;
    bool isRunning;

    std::queue<Task> taskQueue;
    std::mutex mutex_;
    std::condition_variable condition_;
};