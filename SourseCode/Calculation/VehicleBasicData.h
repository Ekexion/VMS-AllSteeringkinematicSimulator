#pragma once
#include"Core.h"

//-------------�����ٶ�----------
const float small_velocity_except = 0.004f;

//-------------���˽��ٶ�----------
const float small_vfi_except = 0.01f;


const float Resis_R_Ratio = 10.0f;



struct VehicleBasicData
{

	//VehicleBasicData();
	//~VehicleBasicData();

	float a;//ǰ���
	float b;//�����

	float B;//�־�

	float hg;//���ĸ�


	float bw;//�ֿ�
	float hw;//�ָ�

	float m;//������

};


//��׼ȷ������������
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




//���������
struct InputOperate
{
	InputOperate(float m, float steering_ratio = 1.0f / 10.0f, float power_allo_ratio_f = 0.5);
		

	//����ת����ת����������ת��,ǰת��
	float outWheelRatio();

	//������ٶȣ�
	//ע�⣡��׼ȷ����ģ��,,vfi_nowΪ��ǰ���ٶȣ�ע���������ٶ��ǽǶ���
	//Ϊ�˸���ʵģ�⣬�صذ�ת��ʱĦ�����󣡣���ת��ʱ������������
	float outAcceleration(const float& v_now, const float& vfi_now);

	//������ݼ��ٶȼ�����ٶȣ����������Ĳ�ƫ����ǰ���һ�½Ƕȣ���ƽ�ƣ�
	float outVelocity_DIAG(const float& deltatime, const float& v_now);

	//������ݼ��ٶȼ�����ٶȣ����������Ĳ�ƫ����ǰ���һ�½Ƕ�90���Ⱥ���
	float outVelocity_LATE(const float& deltatime, const float& v_now);

	//������ݼ��ٶȼ�����ٶȣ�������ǰ��ת�򣨼ȣ�
	//��beta�����Ĳ�ƫ��()��delt��ǰ��ת�ǣ����⣩�� //(���Ѱ���)f_ratioָǰ��ռ�ܶ����ķ������
	float outVelocity_F(const float& deltatime, const float& v_now, const float& beta, const float& delt/*, const float& f_ratio*/);

	//������ݼ��ٶȼ�����ٶȣ�����������ת�򣨼ȣ�
    //��beta�����Ĳ�ƫ��()��delt_f��ǰ��ת�ǣ����⣩��delt_r�Ǻ���ת�ǣ����⣩�� //(���Ѱ���)f_ratioָǰ��ռ�ܶ����ķ������
	float outVelocity_A(const float& deltatime, const float& v_now, const float& beta, const float& delt_f, const float& delt_r/*, const float& f_ratio*/);

	//���ݼ��ٶȼ����ڽ��ٶȣ��������Դ����
	//R������������ʱ��ʱ
	float outVFi_ROUN(const float& deltatime,const float& R, const float& vfi_now);

	float steering_wheel_angle;//������ת��

	float pedalacc_ratio;//����̤����³̶�
	float pedalbra_ratio;//�ƶ�̤����³̶�

	float steering_ratio;//ת���

	float power_allo_ratio_f;//ǰ�ַ���Ĺ��ʱ���

	float m;//����

	float temp_acceleration;//��ʱ�ļ��ٶȣ�ֻ�е��ú���outAcc�����Ÿ���

	float is_LATE_flag;//��ʶ����ģʽ

	float rotcenter_distance_A;//����ת����ת���ľ�����ֵĳ���ͶӰ���루0~L��()

	VehicleForceModel force;//������

};