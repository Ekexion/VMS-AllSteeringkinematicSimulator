#pragma once

#include <string>
#include <iostream>

#include<thread>
#include<mutex>
#include<condition_variable>

#include<functional>


//�߳���ִ�к���
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

	/* ��������ʼ���̳߳���ɣ�
	��ע��,�ú���ֻ����accept����֮ǰ����һ�Σ�
	�ú���Ӧ�������빹�캯����ʼ��ʱ���һ�㣬�ԴﵽЧ�����(����������*/
	void waitThreadReady();
	//��������,���û�п��̣߳��򷵻�flase ��ͬʱ����һ����ǰ�߳�����id
	bool Accept(threadFunc* threadfunc , unsigned int workID);
	//�ͷ�û��������̣߳�����ָ�������������سɹ��ͷŵ��߳�,Ĭ��Ϊ�ͷ����п����߳�
	unsigned int releaseThread(unsigned int num = 0);
	//�����̵߳ĸ���
	unsigned int freeThread() const;
	//��鹲δ�ų������̵߳����߳�
	unsigned int totalThread() const;
	//���������߳�
	unsigned int survivedThread() const;
	//����߳��Ƿ��������
	bool isWorkdown(unsigned int workID);
	
	//��������id�Ƿ����
	bool isWorkIDexsist(const unsigned int workID);

private:
	unsigned int threadnum;
	unsigned int threadtotalnum;

	ThreadCorps** threadlist;
    int* workid;

	
};

