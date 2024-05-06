#include"Suspension.h"





RenderSuspData::RenderSuspData()
	:pos{}, rot{}, RotAxispos{},width(std_Susp_width* COORD_ZOOM), height(std_Susp_Lenth* COORD_ZOOM)

{


	Matrix rottf = MatrixTranslate(this->RotAxispos.x, this->RotAxispos.y, this->RotAxispos.z);

	//创建旋转变换矩阵
	Matrix rotan = MatrixRotateXYZ(this->rot);

	auto rotateTransform = MatrixMultiply(rottf, rotan);


	Matrix posTransform = MatrixTranslate(this->pos.x, this->pos.y, this->pos.z);

	//两个矩阵相乘，得到复合变换矩阵
	this->complexTransform = MatrixMultiply(posTransform, rotateTransform);
}




void RenderSuspData::setSize(const float& w, const float& h)
{
	this->width = w * COORD_ZOOM;
	this->height = h * COORD_ZOOM;

}

void RenderSuspData::setPosAdd(const Vector3& added)
{
	this->pos = { this->pos.x + added.x * COORD_ZOOM, this->pos.y + added.y * COORD_ZOOM,this->pos.z + added.z * COORD_ZOOM };

	Matrix posTransform = MatrixTranslate(added.x * COORD_ZOOM, added.y * COORD_ZOOM, added.z * COORD_ZOOM);

	this->complexTransform = MatrixMultiply(posTransform, this->complexTransform);

}

void RenderSuspData::setPosDir_xz(const Vector2& added)
{

	Matrix posTransform = MatrixTranslate(added.x * COORD_ZOOM - this->pos.x, 0, added.y * COORD_ZOOM - this->pos.z);

	this->pos = { added.x * COORD_ZOOM, this->pos.y, added.y * COORD_ZOOM };


	this->complexTransform = MatrixMultiply(posTransform, this->complexTransform);


}


Suspension::Suspension()
{
	this->model = GenMeshCylinder(this->data.width / 2, this->data.height, Susp_Sides);


	//创建贴图
	Image checked = GenImageColor(1, 1, Susp_Color);// GenImageChecked(2, 2, 1, 1, ColorFromHSV(colorHue, 1, 1),LIGHTGRAY) ,
	Texture2D texture = LoadTextureFromImage(checked);
	UnloadImage(checked);

	//基于贴图创建材质
	this->material = LoadMaterialDefault();
	this->material.maps[MATERIAL_MAP_DIFFUSE].texture = texture;

}

void Suspension::Draw()
{

	//DrawCylinderEx(this->data.l_axis_pos, this->data.r_axis_pos, this->data.axis_height, this->data.axis_height, 4, Body_Color);
	DrawMesh(this->model, this->material, this->data.complexTransform);

}

void Suspension::setSize(const float& w, const float& h)
{


	this->data.setSize(w, h);

	this->model = GenMeshCylinder(this->data.width / 2, this->data.height, Susp_Sides);
}

