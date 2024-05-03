
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

	//�ȼ���̤�壬acc��0~1
	void TurnAcc_dir(const float& acc);

	//��ɲ��̤�壬bra��0~1
	void TurnBrake_dir(const float& bra);

	void Draw() override;


	RenderPedalData data;

private:
	float acc;
	float brake;



};

