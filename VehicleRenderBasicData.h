#pragma once
#include"Wheel.h"
#include "Body.h"
#include "Suspension.h"
#include "SteeringWheel.h"
#include "Pedal.h"
#include"Tracing.h"



struct VehicleRenderBasicData
{
	VehicleRenderBasicData();
	~VehicleRenderBasicData();

	Body body;

	Suspension sfl;//ǰ��
	Suspension sfr;//ǰ��
	Suspension srl;//����
	Suspension srr;//����

	Wheel wfl;//ǰ��
	Wheel wfr;//ǰ��
	Wheel wrl;//����
	Wheel wrr;//����

	Tracing trace_mid;//���Ĺ켣



	SteeringWheel* swdraw;//�����̻��ƣ��ӳ٣���Ϊcontextû��׼����
	Pedal* pedal;//̤����ƣ��ӳ٣���Ϊcontextû��׼����

};
