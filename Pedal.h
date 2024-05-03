
#pragma once
#include"Renderer.h"


struct RenderPedalData
{
	RenderPedalData();

	float scale_acc;
	float scale_bra;

	int w;
	int h;
	

	Vector2 pos;

};



class  Pedal :public RenderObject
{

public:

	Pedal();
	~Pedal() = default;

	//踩加速踏板，acc在0~1
	void TurnAcc_dir(const float& acc);

	//踩刹车踏板，bra在0~1
	void TurnBrake_dir(const float& bra);

	void Draw() override;


	RenderPedalData data;

private:
	float acc;
	float brake;



};

