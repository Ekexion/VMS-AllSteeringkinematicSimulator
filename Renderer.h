#pragma once
#include"Core.h"
#include"RenderObject.h"
#include "InPutEventCallBack.h"

#include<list>
#include "GUIRenderer.h"

using namespace std;



class Renderer
{
public:

	void push_obj(RenderObject* ro, const bool& is3Drender = true);

	void push_GUI(GUIRenderer* gr);

	InPutEventCallBack inrender_func;//����Ⱦ��Ļص�����Ⱥ���������������Ⱦ

protected:
	Renderer();
	~Renderer() = default;


	void Draw();


	void contextUpdata();//��Ҫ�����ĵĸ���

	Camera3D camera;

private:

	list<RenderObject*>  renderobjlist3D;

	list<RenderObject*>  renderobjlist2D;



	list<GUIRenderer*> guirender;
};

