#pragma once


#include "Renderer.h"
#include"VehicleRenderBasicData.h"
#include "VehicleBasicData.h"
#include "VehicleCoord.h"
#include "Axis.h"
#include "Drive.h"
#include"vehicleHUD.h"
#include "SteeringWheel.h"
#include "Building.h"



class Vehicle
{


public:
	Vehicle(const VehicleBasicData& bd);
	~Vehicle();

	void deliverRender(Renderer& r);

	void getCamera(Camera3D* c);


	//检测是否与相撞
	//设置nullptr时停止
	int checkColWithBuilding(Building* building);


	void close_openHUD();

	//计算汽车运动学函数包装器
	Func calcul_vehicle_kinematic;


private:
	
	VehicleBasicData vdata;//车辆基本固有属性

	VehicleRenderBasicData vrenderdata;//车辆渲染基本信息

	VehicleCoord vcoord;//车辆坐标系信息

	Axis axisline;//坐标系绘制




	Drive drive;

	vehicleHUD hud;


	//记录运行到此时的时间（不是delta！）
	//实际上是计算车辆状态专用的
	float timeclock;


	Building* calBuilding;

};

