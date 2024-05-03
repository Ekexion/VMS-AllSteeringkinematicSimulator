#pragma once
#include"Renderer.h"


struct RenderSteeringWheelData
{
	RenderSteeringWheelData();

	float rot;
	float scale;

	Vector2 pos;

};



class SteeringWheel :public RenderObject
{

public:

	SteeringWheel(const char* path = Steering_Wheel_path);
	~SteeringWheel();

	//转动方向盘
	void TurnSteeringWheel_dir(const float& angle);

	void Draw() override;


	RenderSteeringWheelData data;

private:

	Texture2D tex;



};

