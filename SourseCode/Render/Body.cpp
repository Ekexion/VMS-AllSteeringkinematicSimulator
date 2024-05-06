#include "Body.h"





void RenderBodyData::setSize(const float& w, const float& h, const float& a, const float& b)
{
	this->body_width = w * COORD_ZOOM;
	this->body_height = h * COORD_ZOOM;
	this->body_lenth = (a + b) * COORD_ZOOM;

	float p = (a - b) * COORD_ZOOM;

	this->RotAxispos = {p , 0, 0};
	
}

Vector3 Body::getPos()
{
	return { this->data.pos.x / COORD_ZOOM,this->data.pos.y / COORD_ZOOM,this->data.pos.z / COORD_ZOOM };
}

void RenderBodyData::setPosAdd(const Vector3& added)
{
	this->pos = { this->pos.x + added.x * COORD_ZOOM, this->pos.y + added.y * COORD_ZOOM,this->pos.z+ added.z * COORD_ZOOM };

	this->posTransform = MatrixTranslate(this->pos.x, this->pos.y, this->pos.z);


}

void RenderBodyData::setPosDir_xz(const Vector2& added)
{

	this->pos = { added.x * COORD_ZOOM, this->pos.y, added.y * COORD_ZOOM };

	this->posTransform = MatrixTranslate(this->pos.x, this->pos.y, this->pos.z);

}




void RenderBodyData::setRotateItSelfAdd(const Vector3& added)
{
	//Matrix rottf = MatrixTranslate(-this->RotAxispos.x, -this->RotAxispos.y, -this->RotAxispos.z);
	//this->rot = added; //Vector3Add(this->rot, { added.x / 180.0f * PI, added.y / 180.0f * PI, added.z / 180.0f * PI });
	////创建旋转变换矩阵
	//Matrix rotan = MatrixRotateXYZ(this->rot);
	//this->rotateTransform = MatrixMultiply(rottf, rotan);

	
	//创建旋转变换矩阵
	this->rot = Vector3Add(this->rot, { added.x / 180.0f * PI, added.y / 180.0f * PI,added.z / 180.0f * PI });

	Matrix rotan = MatrixRotateXYZ(this->rot);

	Matrix rottf = MatrixTranslate( this->RotAxispos.x, this->RotAxispos.y, this->RotAxispos.z);

	Matrix rot = MatrixMultiply(rottf, rotan);

	this->rotateTransform = rot;
}

void RenderBodyData::setRotateItSelfDir(const Vector3& pos)
{

	this->rot = { pos.x / 180.0f * PI, pos.y / 180.0f * PI,pos.z / 180.0f * PI };

	Matrix rotan = MatrixRotateXYZ(this->rot);

	Matrix rottf = MatrixTranslate(this->RotAxispos.x, this->RotAxispos.y, this->RotAxispos.z);

	Matrix rot = MatrixMultiply(rottf, rotan);

	this->rotateTransform = rot;
}




RenderBodyData::RenderBodyData()
	:pos{}, rot{},RotAxispos{},rotateTransform{},posTransform{},
	body_width(std_Body_width* COORD_ZOOM), body_height(std_Body_height* COORD_ZOOM), body_lenth(std_Body_Lenth* COORD_ZOOM)

{


	this->setRotateItSelfAdd({0,0,0});

	this->setPosAdd({0,0,0});



}

Body::Body()
{
	this->model = GenMeshCube(this->data.body_width, this->data.body_height, this->data.body_lenth);


	//创建贴图
	Image checked = GenImageColor(1, 1, Body_Color);// GenImageChecked(2, 2, 1, 1, ColorFromHSV(colorHue, 1, 1),LIGHTGRAY) ,
	Texture2D texture = LoadTextureFromImage(checked);
	UnloadImage(checked);

	//基于贴图创建材质
	this->material = LoadMaterialDefault();
	this->material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;

}

void Body::Draw()
{

	//DrawCylinderEx(this->data.l_axis_pos, this->data.r_axis_pos, this->data.axis_height, this->data.axis_height, 4, Body_Color);
	DrawMesh(this->model, this->material, MatrixMultiply(this->data.rotateTransform, this->data.posTransform));

}

void Body::setSize(const float& w, const float& h, const float& a, const float& b)
{
	this->data.setSize(w, h, a, b);

	this->model = GenMeshCube(this->data.body_lenth, this->data.body_height, this->data.body_width);
}
