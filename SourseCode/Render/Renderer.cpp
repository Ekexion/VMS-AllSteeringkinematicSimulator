#include "Renderer.h"






void Renderer::push_obj(RenderObject* ro, const bool& is3Drender)
{


	if (is3Drender)
	{
		this->renderobjlist3D.push_back(ro);
	}
	else
	{
		this->renderobjlist2D.push_back(ro);
	}


}





Renderer::Renderer()
	:camera{}
{


	camera.position = { -2.0f, 2.0f, 0.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 40;
	camera.projection = CAMERA_PERSPECTIVE;
	
	if (MSAA == 2)
	{
		
	}

}




void Renderer::Draw()
{


	BeginDrawing();
	ClearBackground(BK_COLOR);

	UpdateCamera(&camera);

	BeginMode3D(camera);


	this->inrender_func.workFuncs();

	

	if (GRID_SWITCH)
	{
		DrawGrid(100, 4);
	}



	for (auto ite = this->renderobjlist3D.begin(); ite != this->renderobjlist3D.end(); ++ite)
	{


		(*ite)->Draw();


	}


	EndMode3D();





	for (auto ite = this->renderobjlist2D.begin(); ite != this->renderobjlist2D.end(); ++ite)
	{


		(*ite)->Draw();


	}



	for (auto ite = this->guirender.begin(); ite != this->guirender.end(); ++ite)
	{
		(*ite)->Draw();
	}




	if (SHOWFPS_SWITCH)
	{
		DrawFPS(5, 0);


		DrawText("Y", 30, 20, 30, GREEN);

		DrawText("X", 5, 40, 30, RED);

		DrawText("-Z", 30, 40, 30, BLUE);

	}


	EndDrawing();




}

void Renderer::contextUpdata()
{

	SetCameraMode(camera, CAMERA_FREE);


}



void Renderer::push_GUI(GUIRenderer* gr)
{
	this->guirender.push_back(gr);
}