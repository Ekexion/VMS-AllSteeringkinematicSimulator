#pragma once
#include"RenderObject.h"


struct RenderWheelData
{
	friend class Wheel;

public:

	RenderWheelData();


	void setPosAdd(const Vector3& added);
	void setPosDir_xz(const Vector2& pos);


	void setRotateItSelfAdd(const Vector3& added);
	void setRotateItSelfDir(const Vector3& pos);

protected:

	void setSize(const float& w, const float& h);


	Vector3 pos;
	Vector3 rot;

	Vector3 RotAxispos;//旋转轴线

	//Matrix complexTransform;

	Matrix rotateTransform;
	Matrix posTransform;

	float width;
	float height;
};



class Wheel :public RenderObject
{
public:
	Wheel();
	~Wheel() = default;

	void Draw() override;

	void setSize(const float& w, const float& h);

	RenderWheelData data;

private:
	 
	Mesh model;

	//基于贴图创建材质
	Material material;

};

