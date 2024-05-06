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


	//����Ƿ�����ײ
	//����nullptrʱֹͣ
	int checkColWithBuilding(Building* building);


	void close_openHUD();

	//���������˶�ѧ������װ��
	Func calcul_vehicle_kinematic;


private:
	
	VehicleBasicData vdata;//����������������

	VehicleRenderBasicData vrenderdata;//������Ⱦ������Ϣ

	VehicleCoord vcoord;//��������ϵ��Ϣ

	Axis axisline;//����ϵ����




	Drive drive;

	vehicleHUD hud;


	//��¼���е���ʱ��ʱ�䣨����delta����
	//ʵ�����Ǽ��㳵��״̬ר�õ�
	float timeclock;


	Building* calBuilding;

};

