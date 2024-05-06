#pragma once
#include"Core.h"
#include"MatTransform.h"

class RenderObject
{
public:
	RenderObject() = default;
	virtual ~RenderObject() = default;

	virtual void Draw() = 0;



};

