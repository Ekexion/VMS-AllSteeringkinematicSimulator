#pragma once
#include"Core.h"
#include"BasicMovementData.h"
#include "VehicleRenderBasicData.h"
#include "VehicleCoord.h"






class Drive
{

	friend class vehicleHUD;

public:

	Drive(VehicleRenderBasicData* vrenderdata, VehicleCoord* vcoord, VehicleBasicData* vbasicdata);
	~Drive() = default;


	//转动方向盘
	void turnSteeringWheel(const float& wantedangle);

	//踩下踏板，一个踩下，另一个一般为0
	void pressPedal(const float& acc_ratio, const float& bra_ratio);

	//根据旋转中心改变后轮转角（四轮转动模式有效）
	void setRotateRearWheel(const float& rotcenter_distance_A);

	//改变转向模式（暴力改变）
	//车轮角度可能改变
	void turnSteeringType_Direct(SteeringType st, const float& wantedangle);

	//需要键盘控制的
	void KeyControl(const bool& keypressUP, const bool& keypressDOWN, const bool& keypressL, const bool& keypressR, const bool& keypressBLANK);

	//记录轨迹
	void recordTrace();


	//计算！！！
	//计算在delta时间内车辆变化(运动学)
	void calculVehicleState(const float& deltatime);


	//在计算后更新车辆渲染信息
	//通常不用调用（calculV里调用了）
	void updataVehicleRender();


	//获取视角
	void getCamera(Camera3D* ca);


	//改变意外事件是否发生
	//-1，发生碰撞
	void changeAccident(const int& code);

protected:

	//改变车辆中心位置(平面xz)（其他附件均会改变）
	void TransVehicleMidPos_add(const Vector2& pos_xz);

	//改变车辆中心横摆角(平面xz)（其他附件均会改变）
	void TransVehicleMidRot_add(const float& addedfai_a);

	//改变车辆中心位置(平面xz)（其他附件均会改变）
	void TransVehicleMidPos_dir(const Vector2& pos_xz);

	//改变车辆中心横摆角(平面xz)（其他附件均会改变）
	void TransVehicleMidRot_dir(const float& addedfai_a);


	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_fl_add(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_fr_add(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_rl_add(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_rr_add(const float& angle);


	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_fl_dir(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_fr_dir(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_rl_dir(const float& angle);
	//在平面转动车轮，坐标系方向时为正
	void TransWheelRotate_rr_dir(const float& angle);

	//改变车辆中心位置(立体xyz)（其他附件均会改变）
	//未实现！
	void TransVehicleMidPos(const Vector3& pos_xyz, const Vector3& rot_xyz) = delete;


	


private:

	//----转动------------------------

	//设置四轮转向转角，前转向模式
	void turnWheelAngle_F(const float& wantedangle);
	//设置四轮转向转角，斜向模式
	void turnWheelAngle_DIAG(const float& wantedangle);
	//设置四轮转向转角，横向模式，默认左转
	void turnWheelAngle_LATE(const bool& wanted_left);
	//设置四轮转向转角，自转模式，默认左转
	void turnWheelAngle_ROUN(const bool& wanted_left);
	//设置四轮转向转角，四转向模式
	void turnWheelAngle_A(const float& wantedangle_wheel_f);


	//---------------------------------------------


	//计算--------------------------------

	void calculVehicleState_F(const float& deltatime);

	void calculVehicleState_DIAG(const float& deltatime);

	void calculVehicleState_LATE(const float& deltatime);

	void calculVehicleState_ROUN(const float& deltatime);

	void calculVehicleState_A(const float& deltatime);

	//-------------------------------------------------



	VehicleRenderBasicData* vrenderdata;
	VehicleCoord* vcoord;
	VehicleBasicData* vbasicdata;

	Camera3D* camera;

	SteeringType steeringtype;

	MovementStateData statedata;

	MovementData movedata;

	WheelMovementData wheeldata;

	VirturlStateData virturldata;

	InputOperate inputope;


	bool instance_speed;//定速（踏板不动）

	float gears;//档位

	float reWheel_ratio;//自动回正

	int accident;//事故标签

};

