#include "Wheel.h"






Wheel::Wheel()
{

	this->model = GenMeshCylinder(this->data.height / 2.0f, this->data.width, Wheel_Sides);
	

	//创建贴图
	Image checked = GenImageColor(1, 1, Wheel_Color);// GenImageChecked(2, 2, 1, 1, ColorFromHSV(colorHue, 1, 1),LIGHTGRAY) ,
	Texture2D texture = LoadTextureFromImage(checked);
	UnloadImage(checked);

	//基于贴图创建材质
	this->material = LoadMaterialDefault();
	this->material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;


}

void Wheel::Draw()
{

	//DrawCylinderEx(this->data.l_axis_pos , this->data.r_axis_pos, this->data.axis_height, this->data.axis_height, Wheel_Sides, Wheel_Color);
	DrawMesh(this->model, this->material, MatrixMultiply(this->data.rotateTransform, this->data.posTransform));
	
	
}

void Wheel::setSize(const float& w, const float& h)
{
	this->data.setSize(w,h);
	
	this->model = GenMeshCylinder(this->data.height / 2.0f, this->data.width, Wheel_Sides);
}



RenderWheelData::RenderWheelData()
	:pos{0,0,0}, rot{90.0 / 180.0f * PI,0,0  }, rotateTransform{}, posTransform{},
	RotAxispos{ 0, -std_Wheel_width * COORD_ZOOM / 2.0f,  0},width( std_Wheel_width * COORD_ZOOM),height(std_Wheel_height * COORD_ZOOM)

{

	this->setRotateItSelfAdd({0,0,0});

	this->setPosAdd({ 0,0,0 });


}




void RenderWheelData::setSize(const float& w, const float& h)
{
	this->width = w * COORD_ZOOM;
	this->height = h * COORD_ZOOM;

	
}



void RenderWheelData::setPosAdd(const Vector3& added)
{

	this->pos = {  (this->pos.x + added.x * COORD_ZOOM), (this->pos.y + added.y * COORD_ZOOM), (this->pos.z + added.z * COORD_ZOOM) };

	//this->posTransform = MatrixMultiply(MatrixTranslate(-added.y * COORD_ZOOM, added.x * COORD_ZOOM, added.z * COORD_ZOOM), this->posTransform);

	//this->pos = { this->pos.x + added.x * COORD_ZOOM, this->pos.y + added.y * COORD_ZOOM,this->pos.z + added.z * COORD_ZOOM };

	this->posTransform = MatrixTranslate(this->pos.x, this->pos.y, this->pos.z);
}

void RenderWheelData::setPosDir_xz(const Vector2& pos)
{


	this->pos = {  (pos.x * COORD_ZOOM), this->pos.y, pos.y * COORD_ZOOM };

	//this->posTransform = MatrixMultiply(MatrixTranslate(-added.y * COORD_ZOOM, added.x * COORD_ZOOM, added.z * COORD_ZOOM), this->posTransform);

	//this->pos = { this->pos.x + added.x * COORD_ZOOM, this->pos.y + added.y * COORD_ZOOM,this->pos.z + added.z * COORD_ZOOM };

	this->posTransform = MatrixTranslate(this->pos.x, this->pos.y, this->pos.z);
}




void RenderWheelData::setRotateItSelfAdd(const Vector3& added)
{


	//创建旋转变换矩阵
	this->rot = Vector3Add(this->rot, { added.x / 180.0f * PI, added.y / 180.0f * PI,added.z / 180.0f * PI });

	Matrix rotan = MatrixRotateXYZ(this->rot);

	Matrix rottf = MatrixTranslate(this->RotAxispos.x, this->RotAxispos.y, this->RotAxispos.z);

	Matrix rot = MatrixMultiply(rottf, rotan);

	this->rotateTransform = rot;



}

void RenderWheelData::setRotateItSelfDir(const Vector3& pos)
{


	//创建旋转变换矩阵
	this->rot = Vector3Add({ 0,0, 90.0 / 180.0f * PI } , { pos.x / 180.0f * PI, pos.y / 180.0f * PI,pos.z / 180.0f * PI });

	Matrix rotan = MatrixRotateXYZ(this->rot);

	Matrix rottf = MatrixTranslate(this->RotAxispos.x, this->RotAxispos.y, this->RotAxispos.z);

	Matrix rot = MatrixMultiply(rottf, rotan);

	this->rotateTransform = rot;

}
