
#pragma once
#include"RenderObject.h"


struct RenderSuspData
{
	friend class Suspension;
public:

	RenderSuspData();


	void setPosAdd(const Vector3& added);
	void setPosDir_xz(const Vector2& added);

protected:

	void setSize(const float& w, const float& h);

	Vector3 pos;
	Vector3 rot;

	Vector3 RotAxispos;//��ת����

	Matrix complexTransform;

	float width;
	float height;
};



class Suspension :public RenderObject
{
public:
	Suspension();
	~Suspension() = default;

	void Draw() override;

	void setSize(const float& w, const float& h);

	RenderSuspData data;

private:
	Mesh model;

	//������ͼ��������
	Material material;



};



