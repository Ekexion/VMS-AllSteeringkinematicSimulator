#pragma once
#include"Core.h"
#include<functional>
#include <list>

using Func = std::function<void(void)>;


class InPutEventCallBack
{
public:
InPutEventCallBack();


//���к���Ⱥ��������ö��
void workFuncs();

//װ���
void pushFunc(const Func& func);

private:
	std::list<Func> funcs;

	
};

