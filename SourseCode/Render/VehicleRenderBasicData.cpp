#include "VehicleRenderBasicData.h"







VehicleRenderBasicData::VehicleRenderBasicData()
	:swdraw(nullptr),pedal(nullptr)
{
}

VehicleRenderBasicData::~VehicleRenderBasicData()
{


	if (this->swdraw != nullptr)
	{

		delete this->swdraw;
		this->swdraw = nullptr;
	}


	if (this->pedal != nullptr)
	{

		delete this->pedal;
		this->pedal = nullptr;
	}

}
