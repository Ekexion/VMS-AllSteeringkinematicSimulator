#pragma once
#include"VehicleBasicData.h"





//��������ϵ
//�Գ�����������Ϊԭ��
//����Ⱦ�����в�𣡣���
class VehicleCoord
{
public:

	void resetBasicData(const VehicleBasicData& data);

	//��ȡ���ĵ�����������λ��
	void setWorldMidPos_xz(const Vector2& pos);

	//��ȡ���ĵ�����������λ��
	void setWorldMidPos(const Vector3& pos);

	inline Vector3 getWheelAxisPos_fl() { return this->wfl; };
	inline Vector3 getWheelAxisPos_fr() { return this->wfr; };
	inline Vector3 getWheelAxisPos_rl() { return this->wrl; };
	inline Vector3 getWheelAxisPos_rr() { return this->wrr; };

	inline Vector3 getSuspAxisPos_fl() { return this->sfl; };
	inline Vector3 getSuspAxisPos_fr() { return this->sfr; };
	inline Vector3 getSuspAxisPos_rl() { return this->srl; };
	inline Vector3 getSuspAxisPos_rr() { return this->srr; };

	Vector3 getMidPos() { return this->midpos; };

	//���ߣ���������ӳ�䵽��������
	//ֻ��������ƽ��XY����Ҫ��ڽ�
	Vector3 mappingTOWorld_Plane(const Vector3& vec, const float& fai);

	//
	float mappingAngleTOWorld_Plane(const float& fai);

private:

	Vector3 midpos;

	Vector3 wfl;
	Vector3 wfr;
	Vector3 wrl;
	Vector3 wrr;

	Vector3 sfl;
	Vector3 sfr;
	Vector3 srl;
	Vector3 srr;

public:

	VehicleCoord(const VehicleBasicData& data);
	~VehicleCoord();
};

