#include "Drive.h"






Drive::Drive(VehicleRenderBasicData* vrenderdata, VehicleCoord* vcoord, VehicleBasicData* vbasicdata)
	:vrenderdata(vrenderdata),vcoord(vcoord),vbasicdata(vbasicdata),virturldata{},
	steeringtype(F_ST),inputope(vbasicdata->m),instance_speed(false),camera(nullptr)
	,reWheel_ratio(0.0),gears(1.0), accident(0)
{


	//预设
	this->inputope.rotcenter_distance_A = this->vbasicdata->b;





}



void Drive::turnSteeringWheel(const float& wantedangle)
{
	this->inputope.steering_wheel_angle = wantedangle;

	this->vrenderdata->swdraw->TurnSteeringWheel_dir(this->inputope.steering_wheel_angle);


	switch (this->steeringtype)
	{

	case SteeringType::A_ST:
	{
		this->turnWheelAngle_A(this->inputope.outWheelRatio());
	}
	break;

	case SteeringType::DIAG:
	{
		this->turnWheelAngle_DIAG(this->inputope.outWheelRatio());

	}
	break;

	case SteeringType::F_ST:
	{
		this->turnWheelAngle_F(this->inputope.outWheelRatio());
	}
	break;

	case SteeringType::LATE:
	{
		this->turnWheelAngle_LATE((this->inputope.outWheelRatio() >= 0));
		//this->turnWheelAngle_DIAG(this->inputope.outWheelRatio());
	}
	break;

	case SteeringType::ROUN:
	{
		this->turnWheelAngle_ROUN(this->inputope.outWheelRatio() >= 0);
	}
	break;




	}


}

void Drive::pressPedal(const float& acc_ratio, const float& bra_ratio)
{
	this->inputope.pedalacc_ratio = acc_ratio;
	this->inputope.pedalbra_ratio = bra_ratio;

	this->vrenderdata->pedal->TurnAcc_dir(this->inputope.pedalacc_ratio);
	this->vrenderdata->pedal->TurnBrake_dir(this->inputope.pedalbra_ratio);


	//--cul
	this->inputope.outAcceleration(sqrt(this->movedata.v_X * this->movedata.v_X + this->movedata.v_Y * this->movedata.v_Y),
		                                this->movedata.v_Fi_a * (this->vbasicdata->a + this->vbasicdata->b) / 2);


}

void Drive::setRotateRearWheel(const float& rotcenter_distance_A)
{


	if (this->steeringtype == A_ST)
	{

		this->inputope.rotcenter_distance_A = rotcenter_distance_A;

		auto wantedangle = cal_DeltRear_A(this->inputope.rotcenter_distance_A, this->inputope.outWheelRatio(), this->vbasicdata->a + this->vbasicdata->b);


		this->virturldata.rearwheel_ratio = wantedangle;

		//akeman！
		float in_f, out_f, in_r, out_r;
		cal_Delt_Akeman_A(in_f, out_f, in_r, out_r,
			this->inputope.rotcenter_distance_A, this->inputope.outWheelRatio(), this->virturldata.rearwheel_ratio,
			this->vbasicdata->a + this->vbasicdata->b, this->vbasicdata->B);


		this->TransWheelRotate_fl_dir(in_f);
		this->TransWheelRotate_fr_dir(out_f);

		this->TransWheelRotate_rl_dir(in_r);
	
		this->TransWheelRotate_rr_dir(out_r);


	}


}


void Drive::turnSteeringType_Direct(SteeringType st, const float& wantedangle)
{
	this->steeringtype = st;

	switch (this->steeringtype)
	{

	case SteeringType::A_ST :
	{
		this->turnWheelAngle_A(wantedangle);
	}
	break;

	case SteeringType::DIAG:
	{
		this->turnWheelAngle_DIAG(wantedangle);

	}
	break;

	case SteeringType::F_ST:
	{
		this->turnWheelAngle_F(wantedangle);
	}
	break;

	case SteeringType::LATE:
	{

		this->turnWheelAngle_LATE((wantedangle < 0));
	}
	break;

	case SteeringType::ROUN:
	{
		this->turnWheelAngle_ROUN(wantedangle >= 0);
	}
	break;




	}

}

void Drive::KeyControl(const bool& keypressUP, const bool& keypressDOWN, const bool& keypressL, const bool& keypressR, const bool& keypressBLANK)
{


	if (keypressUP)
	{
		if (this->inputope.pedalacc_ratio >= 1)
		{
			this->inputope.pedalacc_ratio = 1;
		}
		else
		{
			this->inputope.pedalacc_ratio += 0.1;
		}

		this->pressPedal(this->inputope.pedalacc_ratio, 0);
	}
	else if (keypressDOWN)
	{

		if (this->inputope.pedalbra_ratio >= 1)
		{
			this->inputope.pedalbra_ratio = 1;
		}
		else
		{
			this->inputope.pedalbra_ratio += 0.25;
		}

		this->pressPedal(0, this->inputope.pedalbra_ratio);

	}
	else if (!this->instance_speed)
	{
		this->pressPedal(0, 0);
	}



	if (!keypressBLANK)
	{


		if (keypressL)
		{
			this->inputope.steering_wheel_angle -= 1;
			this->turnSteeringWheel(this->inputope.steering_wheel_angle);
		}
		else if (keypressR)
		{
			this->inputope.steering_wheel_angle += 1;
			this->turnSteeringWheel(this->inputope.steering_wheel_angle);
		}
		else
		{
			if (this->inputope.steering_wheel_angle != 0)
			{
				if (abs(this->inputope.steering_wheel_angle) > this->reWheel_ratio)
				{

					this->inputope.steering_wheel_angle += this->inputope.steering_wheel_angle > 0 ? -this->reWheel_ratio : this->reWheel_ratio;
					this->turnSteeringWheel(this->inputope.steering_wheel_angle);
				}
				else
				{
					this->inputope.steering_wheel_angle = 0;
					this->turnSteeringWheel(this->inputope.steering_wheel_angle);
				}

			}
		}



	}
	else
	{

		if (keypressR)
		{

			if (this->inputope.rotcenter_distance_A <= this->vbasicdata->a + this->vbasicdata->b)
			{
				this->inputope.rotcenter_distance_A += 0.1;

				if (this->inputope.rotcenter_distance_A > this->vbasicdata->a + this->vbasicdata->b)
				{
					this->inputope.rotcenter_distance_A = this->vbasicdata->a + this->vbasicdata->b;

				}
			}

		}
		else if (keypressL)
		{

			if (this->inputope.rotcenter_distance_A > 0)
			{
				this->inputope.rotcenter_distance_A -= 0.1;

				if (this->inputope.rotcenter_distance_A < 0)
				{
					this->inputope.rotcenter_distance_A = 0;

				}
			}


		}


		this->setRotateRearWheel(this->inputope.rotcenter_distance_A);

	}



}



void Drive::recordTrace()
{

	this->vrenderdata->trace_mid.pushTrace_exceptSame({ this->statedata.X, 0 , -this->statedata.Y });

}





void Drive::calculVehicleState(const float& deltatime)
{
	
	switch (this->steeringtype)
	{

	case SteeringType::A_ST:
	{
		this->calculVehicleState_A(deltatime);
	}
	break;

	case SteeringType::DIAG:
	{
		this->calculVehicleState_DIAG(deltatime);
	}
	break;

	case SteeringType::F_ST:
	{
		this->calculVehicleState_F(deltatime);
	}
	break;

	case SteeringType::LATE:
	{
		this->calculVehicleState_LATE(deltatime);
	}
	break;

	case SteeringType::ROUN:
	{
		this->calculVehicleState_ROUN(deltatime);
	}
	break;




	}

	this->updataVehicleRender();

}





void Drive::updataVehicleRender()
{

	this->TransVehicleMidPos_dir({this->statedata.X, this->statedata.Y});

	this->TransVehicleMidRot_dir(this->statedata.Fi_a);


}



void Drive::getCamera(Camera3D* ca)
{
	this->camera = ca;

}

void Drive::changeAccident(const int& code)
{

	this->accident = code;

}





void Drive::turnWheelAngle_F(const float& wantedangle)
{
	//akeman
	float in, out;

	cal_Delt_Akeman(in, out, this->inputope.outWheelRatio(), (this->vbasicdata->a + this->vbasicdata->b), this->vbasicdata->B);


		this->TransWheelRotate_fl_dir(in);
		this->TransWheelRotate_fr_dir(out);


	this->TransWheelRotate_rl_dir(0);
	this->TransWheelRotate_rr_dir(0);
}


void Drive::turnWheelAngle_DIAG(const float& wantedangle)
{


	//在平面转动车轮，坐标系方向顺时为正
	this->TransWheelRotate_fl_dir(wantedangle);
	//在平面转动车轮，坐标系方向顺时为正
	this->TransWheelRotate_fr_dir(wantedangle);
	//在平面转动车轮，坐标系方向顺时为正
	this->TransWheelRotate_rl_dir(wantedangle);
	//在平面转动车轮，坐标系方向顺时为正
	this->TransWheelRotate_rr_dir(wantedangle);

}




void Drive::turnWheelAngle_LATE(const bool& wanted_left)
{


	if (wanted_left)
	{
		this->turnWheelAngle_DIAG(90);
	}
	else
	{
		this->turnWheelAngle_DIAG(-90);
	}

}





void Drive::turnWheelAngle_ROUN(const bool& wanted_left)
{
	float wantedangle_f = 0, wantedangle_r = 0;

	wantedangle_f = atan(this->vbasicdata->B / 2 / this->vbasicdata->a) * 180 / PI;
	wantedangle_r = atan(this->vbasicdata->B / 2 / this->vbasicdata->b) * 180 / PI;


	if (wanted_left)
	{
		
		this->TransWheelRotate_fl_dir(90 + wantedangle_f);
	
		this->TransWheelRotate_fr_dir(90 - wantedangle_f);
	
		this->TransWheelRotate_rl_dir(-(90 + wantedangle_r));
	
		this->TransWheelRotate_rr_dir(-(90 - wantedangle_r));
	}
	else
	{
		this->TransWheelRotate_fl_dir(-(90 - wantedangle_f));

		this->TransWheelRotate_fr_dir(-(90 + wantedangle_f));

		this->TransWheelRotate_rl_dir(90 - wantedangle_r);

		this->TransWheelRotate_rr_dir(90 + wantedangle_r);
	}

	


}



void Drive::turnWheelAngle_A(const float& wantedangle_wheel_f)
{
	

    //akeman，实现移入setRotateRearWheel
	//


	this->setRotateRearWheel(this->inputope.rotcenter_distance_A);



}



void Drive::TransVehicleMidPos_add(const Vector2& pos_xz)
{

	this->statedata.X += pos_xz.x;
	this->statedata.Y += pos_xz.y;



	this->vrenderdata->body.data.setPosAdd({ pos_xz.x, 0 , pos_xz.y });

	this->vrenderdata->wfl.data.setPosAdd({ pos_xz.x,0, pos_xz.y });
	this->vrenderdata->wfr.data.setPosAdd({ pos_xz.x,0, pos_xz.y });
	this->vrenderdata->wrl.data.setPosAdd({ pos_xz.x,0,  pos_xz.y });
	this->vrenderdata->wrr.data.setPosAdd({ pos_xz.x,0 , pos_xz.y });

	this->vrenderdata->sfl.data.setPosAdd({ pos_xz.x,0, pos_xz.y });
	this->vrenderdata->sfr.data.setPosAdd({ pos_xz.x,0, pos_xz.y });
	this->vrenderdata->srl.data.setPosAdd({ pos_xz.x,0,  pos_xz.y });
	this->vrenderdata->srr.data.setPosAdd({ pos_xz.x,0 , pos_xz.y });

}



void Drive::TransVehicleMidRot_add(const float& addedfai)
{
	this->statedata.Fi_a += addedfai;


	this->vrenderdata->body.data.setRotateItSelfAdd({ 0, addedfai, 0 });

	this->vrenderdata->wfl.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->wfr.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->wrl.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->wrr.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));


	this->vrenderdata->sfl.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->sfr.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->srl.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));
	this->vrenderdata->srr.data.setPosAdd(this->vcoord->mappingTOWorld_Plane({ 0,0 }, this->statedata.Fi_a));


	this->vrenderdata->wfl.data.setRotateItSelfAdd({ 0,addedfai, 0 });
	this->vrenderdata->wfr.data.setRotateItSelfAdd({ 0,addedfai, 0 });
	this->vrenderdata->wrl.data.setRotateItSelfAdd({ 0,addedfai, 0 });
	this->vrenderdata->wrr.data.setRotateItSelfAdd({ 0,addedfai, 0 });

}




void Drive::TransVehicleMidPos_dir(const Vector2& p_xz)
{

	this->statedata.X = p_xz.x;
	this->statedata.Y = p_xz.y;

	Vector2 pos_xz = {p_xz.x - this->vrenderdata->body.getPos().x, -(p_xz.y - this->vrenderdata->body.getPos().z)};

	this->vcoord->setWorldMidPos_xz({ this->statedata.X, -this->statedata.Y });

	this->vrenderdata->body.data.setPosDir_xz({ this->statedata.X, -this->statedata.Y });

	this->vrenderdata->wfl.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->wfr.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->wrl.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->wrr.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });

	this->vrenderdata->sfl.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->sfr.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->srl.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });
	this->vrenderdata->srr.data.setPosAdd({ pos_xz.x, 0,  pos_xz.y });


}





void Drive::TransVehicleMidRot_dir(const float& fai)
{

	this->statedata.Fi_a = fai;

	this->vrenderdata->body.data.setRotateItSelfDir({ 0, this->statedata.Fi_a, 0 });


	Vector3 w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getWheelAxisPos_fl(), this->statedata.Fi_a);
	this->vrenderdata->wfl.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getWheelAxisPos_fr(), this->statedata.Fi_a);
	this->vrenderdata->wfr.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getWheelAxisPos_rl(), this->statedata.Fi_a);
	this->vrenderdata->wrl.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getWheelAxisPos_rr(), this->statedata.Fi_a);
	this->vrenderdata->wrr.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getSuspAxisPos_fl(), this->statedata.Fi_a);
	this->vrenderdata->sfl.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getSuspAxisPos_fr(), this->statedata.Fi_a);
	this->vrenderdata->sfr.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getSuspAxisPos_rl(), this->statedata.Fi_a);
	this->vrenderdata->srl.data.setPosDir_xz({ w.x,w.z });

	w = this->vcoord->mappingTOWorld_Plane(this->vcoord->getSuspAxisPos_rr(), this->statedata.Fi_a);
	this->vrenderdata->srr.data.setPosDir_xz({ w.x,w.z });


	this->vrenderdata->wfl.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(this->statedata.Fi_a + this->wheeldata.delt_fl), 0 });
	this->vrenderdata->wfr.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(this->statedata.Fi_a + this->wheeldata.delt_fr), 0 });
	this->vrenderdata->wrl.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(this->statedata.Fi_a + this->wheeldata.delt_rl), 0 });
	this->vrenderdata->wrr.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(this->statedata.Fi_a + this->wheeldata.delt_rr), 0 });

}


void Drive::TransWheelRotate_fl_add(const float& angle)
{

	this->wheeldata.delt_fl += angle;


	this->vrenderdata->wfl.data.setRotateItSelfAdd({ 0,angle, 0 });

}

void Drive::TransWheelRotate_fr_add(const float& angle)
{

	this->wheeldata.delt_fr += angle;

	this->vrenderdata->wfr.data.setRotateItSelfAdd({ 0,angle, 0 });

}

void Drive::TransWheelRotate_rl_add(const float& angle)
{

	this->wheeldata.delt_rl += angle;

	this->vrenderdata->wrl.data.setRotateItSelfAdd({ 0,angle, 0 });
}

void Drive::TransWheelRotate_rr_add(const float& angle)
{
	this->wheeldata.delt_rr += angle;


	this->vrenderdata->wrr.data.setRotateItSelfAdd({ 0,angle, 0 });
}

void Drive::TransWheelRotate_fl_dir(const float& angle)
{
	this->wheeldata.delt_fl = angle;


	this->vrenderdata->wfl.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(angle), 0});
}

void Drive::TransWheelRotate_fr_dir(const float& angle)
{
	this->wheeldata.delt_fr = angle;

	this->vrenderdata->wfr.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(angle), 0 });
}

void Drive::TransWheelRotate_rl_dir(const float& angle)
{
	this->wheeldata.delt_rl = angle;

	this->vrenderdata->wrl.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(angle), 0 });
}

void Drive::TransWheelRotate_rr_dir(const float& angle)
{
	this->wheeldata.delt_rr = angle;

	this->vrenderdata->wrr.data.setRotateItSelfDir({ 0,this->vcoord->mappingAngleTOWorld_Plane(angle), 0 });
}







void Drive::calculVehicleState_F(const float& deltatime)
{

	//
	auto beta = cal_Beta_F(this->vbasicdata->a, this->vbasicdata->b, this->inputope.outWheelRatio());
	
	auto V = this->inputope.outVelocity_F(deltatime, sqrt(this->movedata.v_X * this->movedata.v_X + this->movedata.v_Y * this->movedata.v_Y)
		                                  , beta,  this->inputope.outWheelRatio());


	this->movedata = cal_FST(V, this->inputope.outWheelRatio(), beta, this->statedata.Fi_a, this->vbasicdata->a + this->vbasicdata->b);
	//this->movedata = cal_AST(V, this->inputope.outWheelRatio(),this->wheeldata.delt_rl, beta, this->statedata.Fi, this->vbasicdata->a + this->vbasicdata->b);

	this->statedata = cal_State_Dir(this->statedata, this->movedata, deltatime * this->gears);

	
}



void Drive::calculVehicleState_DIAG(const float& deltatime)
{
	//V应是
	auto V = this->inputope.outVelocity_DIAG(deltatime, sqrt(this->movedata.v_X * this->movedata.v_X + this->movedata.v_Y * this->movedata.v_Y));


	this->movedata = cal_DIAG(this->wheeldata.delt_fl + this->statedata.Fi_a, V);

	this->statedata = cal_State_Dir(this->statedata, this->movedata, deltatime * this->gears);

}



void Drive::calculVehicleState_LATE(const float& deltatime)
{


	//V应是
	auto V = this->inputope.outVelocity_LATE(deltatime, sqrt(this->movedata.v_X * this->movedata.v_X + this->movedata.v_Y * this->movedata.v_Y));
	

	this->movedata = cal_LATE(this->wheeldata.delt_fl + this->statedata.Fi_a, V);
	
	this->statedata = cal_State_Dir(this->statedata, this->movedata, deltatime * this->gears);
	
}



void Drive::calculVehicleState_ROUN(const float& deltatime)
{
	auto R = (this->vbasicdata->a + this->vbasicdata->b) / 2;
	auto V_Fi_a = this->inputope.outVFi_ROUN(deltatime, this->wheeldata.delt_fl > 0 ? R : -R, this->movedata.v_Fi_a);

	this->movedata = cal_ROUN(V_Fi_a);

	this->statedata = cal_State_Dir(this->statedata, this->movedata, deltatime * this->gears);



}



void Drive::calculVehicleState_A(const float& deltatime)
{

	//
	auto beta = cal_Beta_A(this->vbasicdata->a, this->vbasicdata->b,this->inputope.rotcenter_distance_A ,this->inputope.outWheelRatio(), this->virturldata.rearwheel_ratio);

	auto V = this->inputope.outVelocity_A(deltatime, sqrt(this->movedata.v_X * this->movedata.v_X + this->movedata.v_Y * this->movedata.v_Y)
		, beta, this->inputope.outWheelRatio(), this->virturldata.rearwheel_ratio);


	this->movedata = cal_AST(V, this->inputope.outWheelRatio(), this->virturldata.rearwheel_ratio,
		beta, this->statedata.Fi_a, this->vbasicdata->a + this->vbasicdata->b);

	this->statedata = cal_State_Dir(this->statedata, this->movedata, deltatime * this->gears);


}


