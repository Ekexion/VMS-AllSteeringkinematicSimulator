#pragma once
#include"RenderObject.h"


struct RenderBodyData
{
	friend class Body;


public:



     //在原来基础上改变
	void setPosAdd(const Vector3& added);

	//平面上直接改变
	void setPosDir_xz(const Vector2& added);


	void setRotateItSelfAdd(const Vector3& added);
	void setRotateItSelfDir(const Vector3& pos);

	RenderBodyData();

protected:

	//更改尺寸
	void setSize(const float& w, const float& h, const float& a, const float& b);


	Vector3 pos;
	Vector3 rot;

	Vector3 RotAxispos;//旋转轴线

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

	//更改尺寸
	void setSize(const float& w, const float& h, const float& a, const float& b);
	Vector3 getPos();

	RenderBodyData data;

private:
	Mesh model;

	//基于贴图创建材质
	Material material;



};


