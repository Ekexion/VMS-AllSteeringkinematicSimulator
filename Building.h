#pragma once
#include"RenderObject.h"
#include <list>


struct RenderBuildingData
{



	
	Rectangle button;//底部位置{x, y, w, h}

	float height;//高度

	float buttonoffset;//底部距离 0高度 的偏移量，通常为零

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

