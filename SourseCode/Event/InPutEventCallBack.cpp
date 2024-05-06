#include "InPutEventCallBack.h"



InPutEventCallBack::InPutEventCallBack()
{



}




void InPutEventCallBack::workFuncs()
{

	for (auto ite = this->funcs.begin(); ite != this->funcs.end(); ++ite)
	{
		(*ite)();

	}







}

void InPutEventCallBack::pushFunc(const Func& func)
{
	this->funcs.push_back(func);
}

