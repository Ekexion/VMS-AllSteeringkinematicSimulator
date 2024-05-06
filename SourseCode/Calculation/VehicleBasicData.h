#pragma once
#include"Core.h"

//-------------过滤速度----------
const float small_velocity_except = 0.004f;

//-------------过滤角速度----------
const float small_vfi_except = 0.01f;


const float Resis_R_Ratio = 10.0f;



struct VehicleBasicData
{

	//VehicleBasicData();
	//~VehicleBasicData();

	float a;//前轴距
	float b;//后轴距

	float B;//轮距

	float hg;//质心高


	float bw;//轮宽
	float hw;//轮高

	float m;//总质量

};


//不准确的汽车作用力
//drive_force = r_acc * this->pedalbra_ratio;
//brake_force = -r_bra * this->pedalacc_ratio; 
//float resis_force = resis_a + resis_b * v_now * v_now + resis_c * v_now;
// 
struct VehicleForceModel
{
	VehicleForceModel(float r_acc = 20000, float r_bra = 10000, float resis_a = 1000, float resis_b = 10, float resis_c = 50);

	float r_acc;
	float r_bra;

	float resis_a;
	float resis_b;
	float resis_c;

	float resis_r_ratio;
};




//输入的条件
struct InputOperate
{
	InputOperate(float m, float steering_ratio = 1.0f / 10.0f, float power_allo_ratio_f = 0.5);
		

	//根据转角与转向比输出车轮转角,前转角
	float outWheelRatio();

	//输出加速度，
	//注意！不准确，仅模拟,,vfi_now为当前线速度，注意输入线速度是角度制
	//为了更真实模拟，特地把转动时摩擦调大！！！转向时有明显阻力！
	float outAcceleration(const float& v_now, const float& vfi_now);

	//输出根据加速度计算的速度，适用于质心侧偏角与前后角一致角度（既平移）
	float outVelocity_DIAG(const float& deltatime, const float& v_now);

	//输出根据加速度计算的速度，适用于质心侧偏角与前后角一致角度90（既横向）
	float outVelocity_LATE(const float& deltatime, const float& v_now);

	//输出根据加速度计算的速度，适用于前轮转向（既）
	//，beta是质心侧偏角()，delt是前轮转角（虚拟）， //(类已包含)f_ratio指前轮占总动力的分配比例
	float outVelocity_F(const float& deltatime, const float& v_now, const float& beta, const float& delt/*, const float& f_ratio*/);

	//输出根据加速度计算的速度，适用于四轮转向（既）
    //，beta是质心侧偏角()，delt_f是前轮转角（虚拟），delt_r是后轮转角（虚拟）， //(类已包含)f_ratio指前轮占总动力的分配比例
	float outVelocity_A(const float& deltatime, const float& v_now, const float& beta, const float& delt_f, const float& delt_r/*, const float& f_ratio*/);

	//根据加速度计算横摆角速度，适用于自传情况
	//R的正负代表逆时正时
	float outVFi_ROUN(const float& deltatime,const float& R, const float& vfi_now);

	float steering_wheel_angle;//方向盘转角

	float pedalacc_ratio;//加速踏板踩下程度
	float pedalbra_ratio;//制动踏板踩下程度

	float steering_ratio;//转向比

	float power_allo_ratio_f;//前轮分配的功率比例

	float m;//质量

	float temp_acceleration;//暂时的加速度，只有调用函数outAcc（）才更新

	float is_LATE_flag;//标识横向模式

	float rotcenter_distance_A;//四轮转动旋转中心距离后轮的车身投影距离（0~L）()

	VehicleForceModel force;//力计算

};