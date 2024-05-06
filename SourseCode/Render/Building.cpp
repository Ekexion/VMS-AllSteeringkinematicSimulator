#include "Building.h"
#include <stdlib.h>




Building::Building()
{

	
}

Building::~Building()
{
}





void Building::Draw()
{

	for (auto ite = this->data.begin(); ite != this->data.end(); ++ite)
	{

		DrawCube({ ite->button.x, ite->buttonoffset,ite->button.y }, ite->button.height, ite->height, ite->button.width, ite->color);
		DrawCubeWires({ ite->button.x,  ite->buttonoffset,ite->button.y }, ite->button.height, ite->height, ite->button.width, Building_Color_SHAPE);

	}



}



void Building::push_building(const Rectangle& button, const float& height, const float& buttonoffset, Color color)
{



	this->data.push_back({ {button.x * COORD_ZOOM, button.y * COORD_ZOOM, button.width * COORD_ZOOM, button.height * COORD_ZOOM}
	                      , height * COORD_ZOOM, buttonoffset * COORD_ZOOM + height * COORD_ZOOM / 2, color });


}

int Building::checkCo(const Rectangle& rect)
{
	int c = 0;

	for (auto ite = this->data.begin(); ite != this->data.end(); ++ite, ++c)
	{

		if (CheckCollisionRecs(ite->button, { rect.x * COORD_ZOOM , rect.y * COORD_ZOOM , rect.width * COORD_ZOOM , rect.height * COORD_ZOOM }))
		{
			return c;
		}

	}

	return -1;

}
