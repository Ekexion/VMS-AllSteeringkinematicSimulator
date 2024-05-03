#pragma once

#include "GUIRenderer.h"
#include <list>
#include <string>

static int CHART_NAME_INDEX = 0;


enum ChartDataType
{
	INT,
	FLOAT

};



//绘制图表，目前只支持float，int数据
class LineChart :public GUIRenderer
{

public:

	LineChart(const std::string name =  "Chart " + std::to_string(++CHART_NAME_INDEX));
	~LineChart() = default;


	void Draw() override;



	//暂未实现！！！
	template<typename T>
	void push_Data(const std::list<T>& data, const std::string& linename);



	template<typename T>
	void push_Data(const T& dataX, const T& dataY, const std::string& linename);




	void push_Line(const char* name, ChartDataType type, Color color = {0,0,0,0});



private:

	std::string name;

	std::list<std::list<float>> datas_f_Y;

	std::list < std::list<float>> datas_f_X;


	std::list<std::string> float_name;


	std::list<Color> colorbox;

	Rectangle windowbox;

	int window_flag;//1退，2移




	float data_scale_X;
	float data_scale_Y;
	float data_max_X;
	float data_max_Y;

	float data_min_X;
	float data_min_Y;
};




template<typename T>
void LineChart::push_Data(const T& dataX, const T& dataY, const std::string& linename)
{




	if (typeid(T) == typeid(int))
	{
		//auto p = this->datas_i.end();

		//for (auto ite = this->int_name.begin(); ite != this->int_name.end(); ++ite, ++p)
		//{
		//	if (linename == *ite)
		//	{
		//		p->push_back(data);
		//	}
		//}


	}
	else if (typeid(T) == typeid(float))
	{

		if (dataX < this->data_max_X)
		{
			if (dataX < this->data_min_X)
			{
				this->data_min_X = dataX;
			}

		}
		else
		{
			this->data_max_X = dataX;
		}

		if (dataY < this->data_max_Y)
		{
			if (dataY < this->data_min_Y)
			{
				this->data_min_Y = dataY;
			}

		}
		else
		{
			this->data_max_Y = dataY;
		}

		this->data_scale_X = (this->windowbox.width) / (this->data_max_X - this->data_min_X);
		this->data_scale_Y = (this->windowbox.height - 25) / (this->data_max_Y - this->data_min_Y);


		auto px = this->datas_f_X.begin();
		auto py = this->datas_f_Y.begin();

		for (auto ite = this->float_name.begin(); ite != this->float_name.end(); ++ite, ++py, ++px)
		{
			if (linename == *ite)
			{
				
				px->push_back(dataX);
				py->push_back(dataY);
			}
		}
	}
}




template<typename T>
void LineChart::push_Data(const std::list<T>& data, const std::string& linename)
{




}



