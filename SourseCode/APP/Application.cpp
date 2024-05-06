#include "Application.h"










Application::Application()
	:app_terminal(false),close_app_vsm(false)
	,window_vsm(new Window)


	,awd_aws({
		    2.0f,
			2.0f,
			1.6f,
			0.52f,
			0.3f,
			0.8005f,
			1500.0f,
	        })
{
	



	this->awd_aws.getCamera(&this->window_vsm->getCamera());


	
	//CALCUL!
	this->window_vsm->inrender_func.pushFunc(this->awd_aws.calcul_vehicle_kinematic);

	


	//----------------buildingtest----------------------------

	this->build_test.push_building({ 20, -20, 10, 8 });
	this->build_test.push_building({ 30, -20, 10, 8 });
	this->build_test.push_building({ 50, -20, 10, 8 });
	this->build_test.push_building({ 80, -20, 10, 8 });
	this->build_test.push_building({ 80, -40, 10, 8 });
	this->build_test.push_building({ 80, -70, 10, 8 });

	Func f = std::bind(
		[this]() 
		{
			this->awd_aws.checkColWithBuilding(&this->build_test);

		});

	this->window_vsm->inrender_func.pushFunc(f);


	this->awd_aws.deliverRender(*this->window_vsm);
	this->window_vsm->push_obj(&this->build_test);



	//test
	this->window_vsm->push_GUI(&this->testchart);


	this->testchart.push_Line("rand1", FLOAT,RED);
	this->testchart.push_Line("rand2", FLOAT,GREEN);
	this->testchart.push_Line("rand3", FLOAT,BLUE);

}



Application::~Application()
{
	if (this->window_vsm != nullptr)
	{
		delete this->window_vsm;
		this->window_vsm = nullptr;
	}
}

int Application::run()
{
	//test
	this->close_app_ga = true;


	while (!this->app_terminal)
	{

		while (!this->close_app_vsm)
		{


			this->window_vsm->ShowUP();


			if (this->window_vsm->isWindowClose())
			{
				this->close_app_vsm = true;

				delete this->window_vsm;
				this->window_vsm = nullptr;

				//Í¬Ê±¹Ø±Õ
				this->app_terminal = true;
			}


			//TEST
			//this->testchart.push_Data((float)GetTime(), GetRandomValue(-100, 100) /100.0f, "rand1");
			//this->testchart.push_Data((float)GetTime(), (float)(GetRandomValue(-100, 100)) / 10.0f, "rand2");

		}

		while (!this->close_app_ga)
		{



		}


	}



	return 0;


}
