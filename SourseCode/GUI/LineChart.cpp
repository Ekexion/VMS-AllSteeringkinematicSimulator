#include "LineChart.h"











LineChart::LineChart(const std::string name)
	:name(name), windowbox{100,100,640,640},window_flag(0)
{
}




void LineChart::Draw()
{


	if (this->window_flag != 1)
	{
		auto _flag = GuiWindowBox(this->windowbox, this->name.c_str());
		if (_flag == 1)
		{
			this->window_flag = _flag;
		}

		if (GuiButton({ this->windowbox.x + this->windowbox.width - 60,this->windowbox.y+2,20,20 }, "+"))
		{
			this->window_flag = 2;
		}
		if (this->window_flag == 2)
		{
			if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
			{
				this->window_flag = 0;
			}
			
			this->windowbox.x = GetMouseX() - this->windowbox.width/2.0f;
			this->windowbox.y = GetMouseY();
		}



		auto ic = this->colorbox.begin();
		auto posindex = 0;





		auto fxin = this->datas_f_X.begin();
		auto fyin = this->datas_f_Y.begin();

		
		for (auto ite = this->float_name.begin(); ite != this->float_name.end(); ++ite,++fyin,++fxin, ++ic, posindex += 25)
		{
			auto count = 0;
			auto v = new Vector2[fyin->size()];

			DrawText(ite->c_str(), this->windowbox.x + this->windowbox.width - 80, this->windowbox.y + 30 + posindex, 15, *ic);


			for (auto sc = 0; sc < this->windowbox.width; sc += this->windowbox.width / 10)
			{
				auto scx = this->windowbox.x + sc;
				auto scy = this->windowbox.y + this->windowbox.height;

				DrawText(std::to_string(sc / this->data_scale_X + this->data_min_X).c_str(), scx, scy, 12, BLACK);
				DrawLine(scx, scy, scx, scy - 20, BLACK);
			}
			for (auto sc = this->windowbox.height; sc > 0 ; sc -= this->windowbox.height /10)
			{
				auto scx = this->windowbox.x;
				auto scy = this->windowbox.y + sc;

				DrawText(std::to_string((this->windowbox.height - sc) / this->data_scale_Y + this->data_min_Y).c_str(), scx, scy - 12, 12, BLACK);
				DrawLine(scx, scy, scx + 20, scy, BLACK);
			}


			auto dx = fxin->begin();
			for (auto d = fyin->begin(); d != fyin->end(); ++d, ++dx, ++count)
			{

				v[count].x = this->windowbox.x + (*dx) * this->data_scale_X - this->data_min_X * this->data_scale_X;
				v[count].y = this->windowbox.y + this->windowbox.height + (*d) * this->data_scale_Y + this->data_min_Y * this->data_scale_Y;
				
			}

			DrawLineStrip(v, fyin->size(),*ic);


			delete[] v;

		}
		



		//ÔÝÎ´ÊµÏÖ
		//auto i = this->datas_i.begin();
		//for (auto ite = this->int_name.begin(); ite != this->int_name.end(); ++ite, ++i)
		//{



		//	for (auto d = i->begin(); d != i->end(); ++d)
		//	{

		//		//DrawLine();

		//	}



		//}


	}


}










void LineChart::push_Line(const char* name, ChartDataType type, Color color)
{
	if (type == INT)
	{
		//this->int_name.push_back(name);

		//this->datas_i.emplace_back();

	}
	else if(type == FLOAT)
	{
		this->float_name.push_back(name);
		this->datas_f_Y.emplace_back();
		this->datas_f_X.emplace_back();
	}

	if (color.a != 0)
	{

		this->colorbox.push_back(color);
		return;
	}

	int cc = this->colorbox.size();
	if (this->colorbox.size() < 5)
	{
		this->colorbox.push_back({ unsigned char(cc * 51),unsigned char(255 - cc * 51),unsigned char(255 - cc * 51),255});
	}
	else if (this->colorbox.size() < 10)
	{
		cc -= 5;
		this->colorbox.push_back({ 0,unsigned char(cc * 51),0,255 });
	}
	else if (this->colorbox.size() < 15)
	{
		cc -= 10;
		this->colorbox.push_back({ 0,0, unsigned char(cc * 51),255 });
	}
	//else if (this->colorbox.size() < 100)
	//{
	//	this->colorbox.push_back({ unsigned char(cc * 10),0,0,255 });
	//}




}
