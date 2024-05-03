#pragma once
#include"GUIRenderer.h"
#include"Drive.h"
#include <string>



struct HUDData
{
	HUDData();

	int drivemode;

	const char* drivemodename = "FrontSteering;Sideway;Vertical;AllSteering;TurnInPlace";

	int temp_sw_angle;


	bool is_lookatcar;
	bool is_followcar;

	bool is_tracerecord;
	unsigned int countclock;//���
};




class vehicleHUD : public GUIRenderer
{
public:
	vehicleHUD(Drive* drive);
	~vehicleHUD() = default;

	void Draw() override;


	bool drawit;
private:

	Vector2 panelpos;
	Color panelcolor;
	bool drapboxopened;

	bool isbad_modeset;//�Ƿ�ı�ģʽ����



	Drive* drive;

	HUDData data;

};

