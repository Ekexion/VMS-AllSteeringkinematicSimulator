#pragma once
#include"Window.h"
#include"Vehicle.h"
#include "LineChart.h"



class Application
{
public:
	Application();
	~Application();

	int run();



private:

	LineChart testchart;

	Window* window_vsm;
	Window* window_ga;

	Vehicle awd_aws;

	Building build_test;



	bool close_app_vsm;
	bool close_app_ga;

	bool app_terminal;

};

