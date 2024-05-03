#pragma once
#include"RenderObject.h"
#include <list>


struct RenderBuildingData
{



	
	Rectangle button;//�ײ�λ��{x, y, w, h}

	float height;//�߶�

	float buttonoffset;//�ײ����� 0�߶� ��ƫ������ͨ��Ϊ��

	Color color;
};




class Building :public RenderObject
{
public:

	Building();
	~Building();

	void Draw() override;


	void push_building(const Rectangle& button, const float& height = Building_H, const float& buttonoffset = 0, Color color= Building_Color_IN);

	int checkCo(const Rectangle& rect);

private:

	std::list<RenderBuildingData> data;

};

