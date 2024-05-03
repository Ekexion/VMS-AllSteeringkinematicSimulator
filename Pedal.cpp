#include "Pedal.h"




RenderPedalData::RenderPedalData()
	:scale_acc(1),scale_bra(1),w(35),h(50), pos{ 100.0f + w, (float)GetRenderHeight() - h - 5 }
{
}




Pedal::Pedal()
	:acc(0),brake(0)
{

}

void Pedal::TurnAcc_dir(const float& acc)
{
	if (acc != 0)
	{
		this->brake = 0;
		this->data.scale_bra = 1;
	}

    if (acc > 1)
	{
		this->acc = 1;
	}
	else
	{
		this->acc = acc;
	}

	this->data.scale_acc = 1 - this->acc / 3.5;
}



void Pedal::TurnBrake_dir(const float& bra)
{

	if (bra != 0)
	{
		this->acc = 0;
		this->data.scale_acc = 1;
	}




	if (bra > 1)
	{
		this->brake = 1;
	}
	else
	{
		this->brake = bra;
	}

	this->data.scale_bra = 1 - this->brake / 3.5;

}

void Pedal::Draw()
{

	DrawRectangle(this->data.pos.x, this->data.pos.y, 
		this->data.w * this->data.scale_bra, this->data.h * this->data.scale_bra, this->brake == 0 ? PedalRelease_Color : PedalPress_Color);

	DrawRectangle(this->data.pos.x + this->data.w + 5, this->data.pos.y, 
		this->data.w * this->data.scale_acc, this->data.h * this->data.scale_acc, this->acc == 0 ? PedalRelease_Color : PedalPress_Color);

}
