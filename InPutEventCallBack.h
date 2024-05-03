#pragma once
#include"Core.h"
#include<functional>
#include <list>

using Func = std::function<void(void)>;


class InPutEventCallBack
{
public:
InPutEventCallBack();


//运行函数群，无需调用多次
void workFuncs();

//装填函数
void pushFunc(const Func& func);

private:
	std::list<Func> funcs;

	
};

