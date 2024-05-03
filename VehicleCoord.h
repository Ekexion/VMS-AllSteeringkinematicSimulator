#pragma once
#include"VehicleBasicData.h"





//车辆坐标系
//以车辆车身重心为原点
//与渲染坐标有差别！！！
class VehicleCoord
{
public:

	void resetBasicData(const VehicleBasicData& data);

	//获取中心点在世界坐标位置
	void setWorldMidPos_xz(const Vector2& pos);

	//获取中心点在世界坐标位置
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

	//工具，车辆坐标映射到世界坐标
	//只考虑汽车平面XY，需要横摆角
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

