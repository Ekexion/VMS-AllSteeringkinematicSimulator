#pragma once
#include"RenderObject.h"

const unsigned int TRACEPOINT_NUM = 500;





class Tracing :public RenderObject
{
public:
	Tracing(const unsigned int& pointnum = TRACEPOINT_NUM);
	~Tracing();

	void Draw() override;

	//装填新点，但排除相同的位置点（不接收）
	void pushTrace_exceptSame(const Vector3& pointpos);

private:



	unsigned int endpoint;

	unsigned int pointnum;

	unsigned int pointnum_count_total;

	Vector3* pointposse;

};

