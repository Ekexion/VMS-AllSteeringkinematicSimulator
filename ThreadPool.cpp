#include "ThreadPool.h"







ThreadCorps::ThreadCorps(threadFunc* func)
	:threadShouldClose(false) ,threadNoWorks(false) , is_noticed(false), func(func)
{
	this->thread = new std::thread(ThreadCorps::threadLoop , this);
}

ThreadCorps::~ThreadCorps()
{
	this->thread->join();

	delete this->thread;
	this->thread = nullptr;
}


void ThreadCorps::threadLoop(ThreadCorps* thread)
{
	
	std::mutex mutex;
	std::unique_lock<std::mutex> locker(mutex);
	
	while (!thread->threadShouldClose)
	{

		thread->threadNoWorks = true;

		thread->conmand.wait(locker); 		

		thread->threadNoWorks = false;	

		if (thread->func != nullptr)
		{
			(*thread->func)();

			thread->func = nullptr;
		}


	}

	return;
}


ThreadPool::ThreadPool(const unsigned int num)
	:threadnum(num),threadtotalnum(num) 
{
	this->threadlist = new ThreadCorps* [num];
	this->workid = new int[num];

	for (int i = 0; i < num; i++)
	{
		this->threadlist[i] = new ThreadCorps(nullptr);

		this->workid[i] = -1;
	}
}

ThreadPool::~ThreadPool()
{
	this->releaseThread();

	for (int i = 0; i < this->threadtotalnum; i++)
	{
		if (this->threadlist[i] != nullptr)
		{
			std::cout<<"正在强制关闭线程（id）" + std::to_string(this->workid[i]);

			this->threadlist[i]->threadShouldClose = true;
			this->threadlist[i]->conmand.notify_one();

			delete this->threadlist[i]; 
			this->threadlist[i] = nullptr;
			this->threadnum--;
			
		}
	}

	delete[] this->threadlist;
	delete[] this->workid;
}

void ThreadPool::waitThreadReady()
{
    
	int count = 0;
	while (true)
	{
		
		this->threadtotalnum = this->threadtotalnum;
		count = 0; 
		for (int i = 0; i < this->threadtotalnum; i++)
		{

			if (this->threadlist[i]->threadNoWorks)
			{
				count++;
			}
		}
		if (count == this->threadtotalnum)
		{
			return;
		}
	}
}

bool ThreadPool::Accept(threadFunc* threadfunc, unsigned int workID)
{
	for (int i = 0; i < this->threadtotalnum; i++)
	{
		if (this->threadlist[i] != nullptr)
		{

			if (this->threadlist[i]->threadNoWorks && this->threadlist[i]->func == nullptr)
			{
		

				this->threadlist[i]->func = threadfunc;

				while (this->threadlist[i]->threadNoWorks != false)
				{
					this->threadlist[i]->conmand.notify_all();
				}

				//巨大失误！！！
				//this->threadlist[i]->threadNoWorks = false; 

				this->workid[i] = (int)workID;

				return true;
			}
		}
	}

	return false;
}

unsigned int ThreadPool::releaseThread(unsigned int num)
{
	int count = 0;
	for (int i = 0; i < this->threadtotalnum; i++)
	{
		if (this->threadlist[i] != nullptr)
		{
			if (this->threadlist[i]->threadNoWorks)
			{
				this->threadlist[i]->threadShouldClose = true;
				this->threadlist[i]->conmand.notify_one();

				delete this->threadlist[i];
				this->threadlist[i] = nullptr;
				this->threadnum--;

				this->workid[i] = -1;

				count++;
				if (count == num)
				{
					return count;
				}
			}
		}
	}
	return count;
}

unsigned int ThreadPool::freeThread() const
{
	int num = 0;
	for (int i = 0; i < this->threadtotalnum; i++)
	{
		if (this->threadlist[i] != nullptr)
		{
			if (this->threadlist[i]->threadNoWorks)
			{
				num++;
			}
		}
	}
	return num;
}

unsigned int ThreadPool::totalThread() const
{
	return this->threadtotalnum;
}

unsigned int ThreadPool::survivedThread() const
{
	return this->threadnum;
}



bool ThreadPool::isWorkdown(unsigned int workID)
{
	for (int i = 0; i < this->threadtotalnum; i++)
	{
		if (this->threadlist[i] != nullptr)
		{

			if (this->workid[i] == workID)
			{
				if (this->threadlist[i]->threadNoWorks)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	return true;
}



bool ThreadPool::isWorkIDexsist(const unsigned int workID)
{

	for (auto i = 0; i < this->threadnum; ++i)
	{
		if (this->workid[i] == workID)
		{
			return true;
		}
	}
	return false;
}


