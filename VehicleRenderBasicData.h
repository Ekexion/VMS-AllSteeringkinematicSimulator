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

	Suspension sfl;//前左
	Suspension sfr;//前右
	Suspension srl;//后左
	Suspension srr;//后右

	Wheel wfl;//前左
	Wheel wfr;//前右
	Wheel wrl;//后左
	Wheel wrr;//后右

	Tracing trace_mid;//中心轨迹



	SteeringWheel* swdraw;//方向盘绘制，延迟，因为context没有准备好
	Pedal* pedal;//踏板绘制，延迟，因为context没有准备好

};
