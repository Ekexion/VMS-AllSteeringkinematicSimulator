#pragma once
#include"Core.h"

enum SteeringType
{

	F_ST, //ǰ��ת�򣨳��棩

	DIAG, //б��ת��

	LATE, //����ת��(б���˶���������ʽ)

	A_ST, //����ת��

	ROUN,//�Դ�ת��

};


struct VirturlStateData
{



	float rearwheel_ratio;//�������ת�ǣ����г�ģ�͵ģ�


};




//����λ����̬����
//���������� X,Y �����ڽ�
//���ڱ�ʾλ��
struct MovementStateData
{
	float X;//�������ϵ������X����
	float Y;//�������ϵ������Y����

	float Fi_a;//��ڽǣ�ע�⣡�Ƕ��Ƶģ�����


	MovementStateData()
		: X(0), Y(0), Fi_a(0)
	{}

	MovementStateData(const MovementStateData& in);
};


//�����˶���̬����
//�������ٶ� vX,vY �����ڽ��ٶ�
//���ڼ���λ��Ԥ��
struct MovementData
{
	float v_X;//x��˲ʱ�ٶ�
	float v_Y;//y��˲ʱ�ٶ�

	float v_Fi_a;//��ڽ�˲ʱ�ٶȣ�ע�⣡�Ƕ��Ƶģ�����
	MovementData(const MovementData& in);
	MovementData()
		: v_X(0), v_Y(0), v_Fi_a(0) {};
};

//������������
//����������ת��
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


//������ٶ�
float cal_Acceleration(const float& m_, const float& force);


//�����ٶ�
float cal_Velocity(const float& a, const float& v_old, const float& delta_time);


//������̬���ӵ���
MovementStateData cal_State_Add(const MovementData& in, const float& delta_time);

//������̬����
MovementStateData cal_State_Dir(const MovementStateData& old_state, const MovementData& in, const float& delta_time);


//����ǰ��ת��ʱ���Ĳ�ƫ�ǣ�����ת�������
float cal_Beta_F(const float& a, const float& b, const float& delt_f);

//��������ת��ʱ���Ĳ�ƫ�ǣ�����ת�������
float cal_Beta_A(const float& a, const float& b, const float& rotcenter_distance_A, const float& delt_f, const float& delt_r);

//�������۶��ǣ��󰢿���ʵ�ʵ�ת��ǣ�ǰ��ת��
void cal_Delt_Akeman(float& inr_delt, float& outr_delt, const float& delt_virtual, const float& L, const float& B);

//�������۶��ǣ��󰢿���ʵ�ʵ�ת��ǣ����֣�����ת��
void cal_Delt_Akeman_A(float& inr_delt_f, float& outr_delt_f, float& inr_delt_r, float& outr_delt_r, 
	                   const float& rotcenter_distance_A, const float& delt_virtual_f, const float& delt_virtual_r, const float& L, const float& B);

//������ת����λ�ü������ת��()
float cal_DeltRear_A(const float& rotcenter_distance_A, const float& delt_f, const float& L);


//ǰ��ת��
//���뵱ǰ����,  ǰ��ת��delte����ʱ��Ϊǰ������ת��һ�£���ɸģ���,    ���Ĳ�ƫ��beta,    ��ڽ�fi��  �����
MovementData cal_FST(const float& v, const float& delt, const float& beta, const float& fi, const float& L);

//����ת��
//���뵱ǰ����,  ǰ��ת��delt_f ������ת��delt_r����ʱ��Ϊǰ������ת��һ�£���ɸģ���,   ���Ĳ�ƫ��beta,   ��ڽ�fi��  �����
MovementData cal_AST(const float& v, const float& delt_f, const float& delt_r, const float& beta, const float& fi, const float& L);


//б��ת��
//���뺽��ǣ�����ת��(�����Ĳ�ƫ��)(��ģʽ��һ�µ�) + ��ڽǣ����ĳ���ת��һ�£����뵱ǰ����
MovementData cal_DIAG(const float& sita, const float& v);

//����ת��
//���뺽��ǣ�����ת��(�����Ĳ�ƫ��)(��ģʽ��һ�µ�) + ��ڽǣ����ĳ���ת��һ�£����뵱ǰ����
MovementData cal_LATE(const float& sita, const float& v);

//ԭ��ת��
//�����ڽ��ٶ�
MovementData cal_ROUN(const float& v_fi);