#include "Window.h"








Window::Window(const unsigned int& WINDOW_W, const unsigned int& WINDOW_H, const char* name)

{
	InitWindow(WINDOW_W, WINDOW_H, name);
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(60);


	Renderer::contextUpdata();
	

}




Window::~Window()
{
	CloseWindow();

}






int Window::ShowUP()
{






		Draw();









	return 0;
}

bool Window::isWindowClose()
{
	return WindowShouldClose();
}

Camera3D& Window::getCamera()
{
	return Renderer::camera;
}
