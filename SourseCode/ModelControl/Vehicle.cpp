#include "Vehicle.h"




Vehicle::Vehicle(const VehicleBasicData& bd)
	:vdata{bd},vcoord(vdata),vrenderdata(),drive(&this->vrenderdata, &this->vcoord, &this->vdata),hud(&this->drive),timeclock(0)
{
	

	//尺寸初始化
	this->vrenderdata.body.setSize(this->vdata.B, this->vdata.hg * 1.0f, this->vdata.a ,this->vdata.b);

	this->vrenderdata.wfl.setSize(this->vdata.bw, this->vdata.hw);
	this->vrenderdata.wfr.setSize(this->vdata.bw, this->vdata.hw);
	this->vrenderdata.wrl.setSize(this->vdata.bw, this->vdata.hw);
	this->vrenderdata.wrr.setSize(this->vdata.bw, this->vdata.hw);

	this->vrenderdata.sfl.setSize(this->vdata.bw / 3.0f, this->vdata.hg - this->vdata.hw / 2.0f);
	this->vrenderdata.sfr.setSize(this->vdata.bw / 3.0f, this->vdata.hg - this->vdata.hw / 2.0f);
	this->vrenderdata.srl.setSize(this->vdata.bw / 3.0f, this->vdata.hg - this->vdata.hw / 2.0f);
	this->vrenderdata.srr.setSize(this->vdata.bw / 3.0f, this->vdata.hg - this->vdata.hw / 2.0f);



	//位置初始化
	Vector3 midpod = { 0, (vdata.hg) , 0 };

	this->vcoord.resetBasicData(this->vdata);
	this->vcoord.setWorldMidPos(midpod);
	
	this->vrenderdata.body.data.setPosAdd(midpod);//暂时

	this->vrenderdata.wfl.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getWheelAxisPos_fl(), 0));
	this->vrenderdata.wfr.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getWheelAxisPos_fr(), 0));
	this->vrenderdata.wrl.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getWheelAxisPos_rl(), 0));
	this->vrenderdata.wrr.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getWheelAxisPos_rr(), 0));

	
	this->vrenderdata.sfl.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getSuspAxisPos_fl(), 0));
	this->vrenderdata.sfr.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getSuspAxisPos_fr(), 0));
	this->vrenderdata.srl.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getSuspAxisPos_rl(), 0));
	this->vrenderdata.srr.data.setPosAdd(this->vcoord.mappingTOWorld_Plane(this->vcoord.getSuspAxisPos_rr(), 0));



	//方程初始化

	this->calcul_vehicle_kinematic = std::bind(
		[this]()
		{
			float t = GetTime();

			if(this->timeclock != 0)
			this->drive.calculVehicleState(t - this->timeclock);

			this->timeclock = t;
		}
	);


}

Vehicle::~Vehicle()
{



}




void Vehicle::deliverRender(Renderer& r)
{

	r.push_obj(&this->vrenderdata.wfl);
	r.push_obj(&this->vrenderdata.wfr);
	r.push_obj(&this->vrenderdata.wrl);
	r.push_obj(&this->vrenderdata.wrr);

	r.push_obj(&this->vrenderdata.body);

	r.push_obj(&this->vrenderdata.sfl);
	r.push_obj(&this->vrenderdata.sfr);
	r.push_obj(&this->vrenderdata.srl);
	r.push_obj(&this->vrenderdata.srr);


	r.push_obj(&this->vrenderdata.trace_mid);

	r.push_obj(&this->axisline);



	if (this->vrenderdata.pedal == nullptr)
	{
		this->vrenderdata.pedal = new Pedal;

	}
	r.push_obj(this->vrenderdata.pedal, false);

	if (this->vrenderdata.swdraw == nullptr)
	{
		this->vrenderdata.swdraw = new SteeringWheel;

	}
	r.push_obj(this->vrenderdata.swdraw, false);
	




	r.push_GUI(&this->hud);

}

void Vehicle::getCamera(Camera3D* c)
{

	this->drive.getCamera(c);


}

int Vehicle::checkColWithBuilding(Building* building)
{
	this->calBuilding = building;
	auto c = this->calBuilding->checkCo({ this->vcoord.getMidPos().x, this->vcoord.getMidPos().z ,this->vdata.a + this->vdata.b, this->vdata.a + this->vdata.b });

	if (c >= 0)
	{
	    this->drive.changeAccident(-1);
	}
	

	return c;
}

void Vehicle::close_openHUD()
{
	this->hud.drawit = !this->hud.drawit;

}





