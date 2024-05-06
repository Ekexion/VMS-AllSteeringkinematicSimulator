#pragma once
#include"Core.h"


class GUIRenderer
{
public:

	virtual void Draw() = 0;



	GUIRenderer() = default;
	virtual ~GUIRenderer() = default;


};

