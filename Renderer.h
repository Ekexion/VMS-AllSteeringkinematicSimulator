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

	InPutEventCallBack inrender_func;//在渲染里的回调函数群，甚至可以添加渲染

protected:
	Renderer();
	~Renderer() = default;


	void Draw();


	void contextUpdata();//需要上下文的更新

	Camera3D camera;

private:

	list<RenderObject*>  renderobjlist3D;

	list<RenderObject*>  renderobjlist2D;



	list<GUIRenderer*> guirender;
};

