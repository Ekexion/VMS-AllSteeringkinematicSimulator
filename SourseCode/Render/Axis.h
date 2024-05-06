#pragma once
#include"RenderObject.h"


struct RenderAxisData
{
	friend class Axis;


public:



	//在原来基础上改变
	void setPosAdd(const Vector3& added);



	RenderAxisData();

protected:

	//更改尺寸
	void setSize(const float& l);


	Vector3 pos_0;

	Vector3 x;
	Vector3 y;
	Vector3 antiz;

	float line_lenth;
};



class Axis :public RenderObject
{



public:
	Axis() = default;
	~Axis() = default;

	void Draw() override;

	//更改尺寸
	void setSize(const float& l);

	RenderAxisData data;

private:

};

