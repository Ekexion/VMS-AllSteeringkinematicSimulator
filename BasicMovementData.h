#pragma once
#include"Core.h"

enum SteeringType
{

	F_ST, //前轮转向（常规）

	DIAG, //斜向转向

	LATE, //横向转向(斜向运动的特殊形式)

	A_ST, //四轮转向

	ROUN,//自传转向

};


struct VirturlStateData
{



	float rearwheel_ratio;//虚拟后轮转角（自行车模型的）


};




//车辆位置姿态数据
//包括：距离 X,Y ，与横摆角
//用于表示位置
struct MovementStateData
{
	float X;//大地坐标系，质心X距离
	float Y;//大地坐标系，质心Y距离

	float Fi_a;//横摆角，注意！角度制的！！！


	MovementStateData()
		: X(0), Y(0), Fi_a(0)
	{}

	MovementStateData(const MovementStateData& in);
};


//车辆运动姿态数据
//包括：速度 vX,vY ，与横摆角速度
//用于计算位置预估
struct MovementData
{
	float v_X;//x轴瞬时速度
	float v_Y;//y轴瞬时速度

	float v_Fi_a;//横摆角瞬时速度，注意！角度制的！！！
	MovementData(const MovementData& in);
	MovementData()
		: v_X(0), v_Y(0), v_Fi_a(0) {};
};

//车辆车轮数据
//包括：四轮转角
//
struct WheelMovementData
{
	float delt_fl;//
	float delt_fr;//
	float delt_rl;
	float delt_rr;//

	WheelMovementData(const WheelMovementData& in);
	WheelMovementData()
		: delt_fl(0), delt_fr(0), delt_rl(0), delt_rr(0) {};
};


//计算加速度
float cal_Acceleration(const float& m_, const float& force);


//计算速度
float cal_Velocity(const float& a, const float& v_old, const float& delta_time);


//计算姿态增加的量
MovementStateData cal_State_Add(const MovementData& in, const float& delta_time);

//计算姿态最终
MovementStateData cal_State_Dir(const MovementStateData& old_state, const MovementData& in, const float& delta_time);


//计算前轮转向时质心侧偏角，根据转角与轴距
float cal_Beta_F(const float& a, const float& b, const float& delt_f);

//计算四轮转向时质心侧偏角，根据转角与轴距
float cal_Beta_A(const float& a, const float& b, const float& rotcenter_distance_A, const float& delt_f, const float& delt_r);

//根据理论动角，求阿克曼实际的转向角（前轮转向）
void cal_Delt_Akeman(float& inr_delt, float& outr_delt, const float& delt_virtual, const float& L, const float& B);

//根据理论动角，求阿克曼实际的转向角（四轮（异向）转向）
void cal_Delt_Akeman_A(float& inr_delt_f, float& outr_delt_f, float& inr_delt_r, float& outr_delt_r, 
	                   const float& rotcenter_distance_A, const float& delt_virtual_f, const float& delt_virtual_r, const float& L, const float& B);

//根据旋转中心位置计算后轮转角()
float cal_DeltRear_A(const float& rotcenter_distance_A, const float& delt_f, const float& L);


//前轮转向
//输入当前车速,  前轮转角delte（此时认为前轮左右转角一致（后可改））,    质心侧偏角beta,    横摆角fi，  与轴距
MovementData cal_FST(const float& v, const float& delt, const float& beta, const float& fi, const float& L);

//四轮转向
//输入当前车速,  前轮转角delt_f ，后轮转角delt_r（此时认为前轮左右转角一致（后可改））,   质心侧偏角beta,   横摆角fi，  与轴距
MovementData cal_AST(const float& v, const float& delt_f, const float& delt_r, const float& beta, const float& fi, const float& L);


//斜向转向
//输入航向角（车轮转角(或质心侧偏角)(此模式是一致的) + 横摆角）（四车轮转角一致），与当前车速
MovementData cal_DIAG(const float& sita, const float& v);

//横向转向
//输入航向角（车轮转角(或质心侧偏角)(此模式是一致的) + 横摆角）（四车轮转角一致），与当前车速
MovementData cal_LATE(const float& sita, const float& v);

//原地转向
//输入横摆角速度
MovementData cal_ROUN(const float& v_fi);