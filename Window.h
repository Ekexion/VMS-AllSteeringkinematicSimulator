#pragma once
#include"Core.h"
#include"Renderer.h"



class Window :public Renderer
{
public:
	Window(const unsigned int& WINDOW_W = WINDOW_W, const unsigned int& WINDOW_H = WINDOW_H, const char* name = APPNAME);
	~Window();


	int ShowUP();

	bool isWindowClose();

	Camera3D& getCamera();

private:
	





};

