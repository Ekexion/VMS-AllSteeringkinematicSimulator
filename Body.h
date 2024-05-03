#pragma once
#include"RenderObject.h"


struct RenderBodyData
{
	friend class Body;


public:



     //��ԭ�������ϸı�
	void setPosAdd(const Vector3& added);

	//ƽ����ֱ�Ӹı�
	void setPosDir_xz(const Vector2& added);


	void setRotateItSelfAdd(const Vector3& added);
	void setRotateItSelfDir(const Vector3& pos);

	RenderBodyData();

protected:

	//���ĳߴ�
	void setSize(const float& w, const float& h, const float& a, const float& b);


	Vector3 pos;
	Vector3 rot;

	Vector3 RotAxispos;//��ת����

	Matrix posTransform;
	Matrix rotateTransform;

	float body_width;
	float body_height;
	float body_lenth;
};



class Body :public RenderObject
{



public:
	Body();
	~Body() = default;

	void Draw() override;

	//���ĳߴ�
	void setSize(const float& w, const float& h, const float& a, const float& b);
	Vector3 getPos();

	RenderBodyData data;

private:
	Mesh model;

	//������ͼ��������
	Material material;



};


