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


	//ת��������
	void turnSteeringWheel(const float& wantedangle);

	//����̤�壬һ�����£���һ��һ��Ϊ0
	void pressPedal(const float& acc_ratio, const float& bra_ratio);

	//������ת���ĸı����ת�ǣ�����ת��ģʽ��Ч��
	void setRotateRearWheel(const float& rotcenter_distance_A);

	//�ı�ת��ģʽ�������ı䣩
	//���ֽǶȿ��ܸı�
	void turnSteeringType_Direct(SteeringType st, const float& wantedangle);

	//��Ҫ���̿��Ƶ�
	void KeyControl(const bool& keypressUP, const bool& keypressDOWN, const bool& keypressL, const bool& keypressR, const bool& keypressBLANK);

	//��¼�켣
	void recordTrace();


	//���㣡����
	//������deltaʱ���ڳ����仯(�˶�ѧ)
	void calculVehicleState(const float& deltatime);


	//�ڼ������³�����Ⱦ��Ϣ
	//ͨ�����õ��ã�calculV������ˣ�
	void updataVehicleRender();


	//��ȡ�ӽ�
	void getCamera(Camera3D* ca);


	//�ı������¼��Ƿ���
	//-1��������ײ
	void changeAccident(const int& code);

protected:

	//�ı䳵������λ��(ƽ��xz)��������������ı䣩
	void TransVehicleMidPos_add(const Vector2& pos_xz);

	//�ı䳵�����ĺ�ڽ�(ƽ��xz)��������������ı䣩
	void TransVehicleMidRot_add(const float& addedfai_a);

	//�ı䳵������λ��(ƽ��xz)��������������ı䣩
	void TransVehicleMidPos_dir(const Vector2& pos_xz);

	//�ı䳵�����ĺ�ڽ�(ƽ��xz)��������������ı䣩
	void TransVehicleMidRot_dir(const float& addedfai_a);


	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_fl_add(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_fr_add(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_rl_add(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_rr_add(const float& angle);


	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_fl_dir(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_fr_dir(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_rl_dir(const float& angle);
	//��ƽ��ת�����֣�����ϵ����ʱΪ��
	void TransWheelRotate_rr_dir(const float& angle);

	//�ı䳵������λ��(����xyz)��������������ı䣩
	//δʵ�֣�
	void TransVehicleMidPos(const Vector3& pos_xyz, const Vector3& rot_xyz) = delete;


	


private:

	//----ת��------------------------

	//��������ת��ת�ǣ�ǰת��ģʽ
	void turnWheelAngle_F(const float& wantedangle);
	//��������ת��ת�ǣ�б��ģʽ
	void turnWheelAngle_DIAG(const float& wantedangle);
	//��������ת��ת�ǣ�����ģʽ��Ĭ����ת
	void turnWheelAngle_LATE(const bool& wanted_left);
	//��������ת��ת�ǣ���תģʽ��Ĭ����ת
	void turnWheelAngle_ROUN(const bool& wanted_left);
	//��������ת��ת�ǣ���ת��ģʽ
	void turnWheelAngle_A(const float& wantedangle_wheel_f);


	//---------------------------------------------


	//����--------------------------------

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


	bool instance_speed;//���٣�̤�岻����

	float gears;//��λ

	float reWheel_ratio;//�Զ�����

	int accident;//�¹ʱ�ǩ

};

