#pragma once
#include"RenderObject.h"


struct RenderAxisData
{
	friend class Axis;


public:



	//��ԭ�������ϸı�
	void setPosAdd(const Vector3& added);



	RenderAxisData();

protected:

	//���ĳߴ�
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

	//���ĳߴ�
	void setSize(const float& l);

	RenderAxisData data;

private:

};

