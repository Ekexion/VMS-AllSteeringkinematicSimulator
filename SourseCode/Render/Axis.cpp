#include "Axis.h"



void RenderAxisData::setPosAdd(const Vector3& added)
{
	this->pos_0 = Vector3Add(this->pos_0, added);

}



RenderAxisData::RenderAxisData()
	:line_lenth(10), pos_0(), x{1,0,0},y{0,1,0}, antiz{0,0,-1}
{

	this->setSize(line_lenth);

}

void RenderAxisData::setSize(const float& l)
{
	
	Vector3Normalize(this->x);
	Vector3Normalize(this->y);
	Vector3Normalize(this->antiz);

	this->line_lenth = l;

	Vector3 t = {this->line_lenth, this->line_lenth, this->line_lenth};
	
	this->x = Vector3Multiply(t, this->x);
	this->y = Vector3Multiply(t, this->y);
	this->antiz = Vector3Multiply(t, this->antiz);
}



void Axis::Draw()
{
	float w_1 = 0.05 * COORD_ZOOM, w_2 = 0.02 * COORD_ZOOM;

	DrawCylinderEx(this->data.pos_0, Vector3Add(this->data.pos_0, this->data.x),w_1, w_2 , 3, RED);

	DrawCylinderEx(this->data.pos_0, Vector3Add(this->data.pos_0, this->data.y), w_1, w_2, 3, GREEN);

	DrawCylinderEx(this->data.pos_0, Vector3Add(this->data.pos_0, this->data.antiz), w_1, w_2, 3, BLUE);



	//DrawText("X", )
		
}




void Axis::setSize(const float& l)
{

	return this->data.setSize(l);
}
