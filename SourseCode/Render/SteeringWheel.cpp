#include "SteeringWheel.h"



SteeringWheel::SteeringWheel(const char* path)
{

	this->tex = LoadTexture(path);

	
}

SteeringWheel::~SteeringWheel()
{
	UnloadTexture(this->tex);
}




void SteeringWheel::TurnSteeringWheel_dir(const float& angle)
{
	this->data.rot = angle/* / 180 * PI*/;
}

void SteeringWheel::Draw()
{

	//DrawTextureEx(this->tex, this->data.pos, ++this->data.rot, this->data.scale, WHITE);
	float w = this->tex.width;
	float h = this->tex.height;

	DrawTexturePro(this->tex, { 0,0,w, h }, { this->data.pos.x,this->data.pos.y,w * this->data.scale,h * this->data.scale},
		           { w * this->data.scale / 2.0f, h * this->data.scale / 2.0f }, this->data.rot, WHITE);
}


RenderSteeringWheelData::RenderSteeringWheelData()
	:rot(3), scale(0.4), pos{80 ,float(GetRenderHeight() - 80)}
{
}
