#pragma once

#include <string>
#include <iostream>

#include<thread>
#include<mutex>
#include<condition_variable>

#include<functional>


//线程内执行函数
using threadFunc = std::function<void(void)>;


struct  ThreadCorps
{
	bool threadShouldClose;
	bool threadNoWorks;

	bool is_noticed;

	threadFunc* func;

	std::thread* thread;

	std::condition_variable conmand;



	ThreadCorps(threadFunc* func);
	~ThreadCorps();

	static void threadLoop(ThreadCorps* thread);
};


class  ThreadPool
{
public:

	ThreadPool(const unsigned int num);
	~ThreadPool();

	/* 阻塞到初始化线程池完成；
	请注意,该函数只能在accept（）之前调用一次；
	该函数应尽量距离构造函数初始化时间久一点，以达到效率最大化(不阻塞）；*/
	void waitThreadReady();
	//接受任务,如果没有空线程，则返回flase ，同时设立一个当前线程任务id
	bool Accept(threadFunc* threadfunc , unsigned int workID);
	//释放没有任务的线程，可以指定个数，并返回成功释放的线程,默认为释放所有空闲线程
	unsigned int releaseThread(unsigned int num = 0);
	//检查空线程的个数
	unsigned int freeThread() const;
	//检查共未排除销毁线程的总线程
	unsigned int totalThread() const;
	//检查存留的线程
	unsigned int survivedThread() const;
	//检查线程是否完成任务
	bool isWorkdown(unsigned int workID);
	
	//检测该任务id是否存在
	bool isWorkIDexsist(const unsigned int workID);

private:
	unsigned int threadnum;
	unsigned int threadtotalnum;

	ThreadCorps** threadlist;
    int* workid;

	
};

