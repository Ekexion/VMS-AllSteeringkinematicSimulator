#include "VehicleCoord.h"



void VehicleCoord::resetBasicData(const VehicleBasicData& data)
{
	Vector3 _wheel = { 0,0, -(data.hg - data.hw / 2.0f) };//{ midpos.x, midpos.z, midpos.y };
	

	this->wfl = { data.a + _wheel.x, data.B / 2.0f + _wheel.y, _wheel.z };
	this->wfr = { data.a + _wheel.x, -data.B / 2.0f + _wheel.y, _wheel.z };
	this->wrl = { -data.b + _wheel.x, data.B / 2.0f + _wheel.y, _wheel.z };
	this->wrr = { -data.b + _wheel.x, -data.B / 2.0f + _wheel.y, _wheel.z };

	this->sfl = { this->wfl.x, this->wfl.y - data.bw / 1.0f, this->wfl.z };
	this->sfr = { this->wfr.x, this->wfr.y + data.bw / 1.0f, this->wfr.z };
	this->srl = { this->wrl.x, this->wrl.y - data.bw / 1.0f, this->wrl.z };
	this->srr = { this->wrr.x, this->wrr.y + data.bw / 1.0f, this->wrr.z };

}

void VehicleCoord::setWorldMidPos_xz(const Vector2& pos)
{
	this->midpos.x = pos.x;
	this->midpos.z = pos.y;

}

void VehicleCoord::setWorldMidPos(const Vector3& pos)
{
	this->midpos = pos;

}

Vector3 VehicleCoord::mappingTOWorld_Plane(const Vector3& vec, const float& fai)
{
	float fai_r = fai / 180 * PI;

	Vector3 vec_vcord = vec;

	float b_angle = abs(atan(vec.y / vec.x));
	float len_xy = sqrt(vec.x * vec.x  +  vec.y * vec.y);
	
	if (vec.x < 0)
	{
		if (vec.y > 0)
		{
			b_angle = PI - b_angle;
		}
		else
		{
			b_angle += PI;
		}
	}
	else if (vec.y < 0)
	{
		b_angle = PI * 2 - b_angle;
	}
	
	

	vec_vcord.x = cos(fai_r + b_angle) * len_xy;
	vec_vcord.y = sin(fai_r + b_angle) * len_xy;
	//vec_vcord.z = vec.z;

	return Vector3Add({vec_vcord.x , vec_vcord.z, -vec_vcord.y,}, this->midpos);
}

float VehicleCoord::mappingAngleTOWorld_Plane(const float& fai)
{
	return fai + 90;
}





VehicleCoord::VehicleCoord(const VehicleBasicData& data)
{
	this->resetBasicData(data);
}


VehicleCoord::~VehicleCoord()
{
	
}
