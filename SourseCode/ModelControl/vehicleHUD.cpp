#include "vehicleHUD.h"






vehicleHUD::vehicleHUD(Drive* drive)
	:drive(drive),drapboxopened(false),isbad_modeset(false),drawit(true)
{

	this->panelcolor = DARKGRAY;

	this->panelpos = { GetRenderWidth() - 251.0f, 0 };

	Font font = GetFontDefault(); 
	font.baseSize = 6;
	GuiSetFont(font);
}




void vehicleHUD::Draw()
{
	
	if (drawit)
	{

		GuiPanel({ this->panelpos.x, this->panelpos.y ,245,920 }, " VMS HUD ");


		//运动显示

		auto st = "PosX: " + std::to_string(this->drive->statedata.X);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 70, 18, BLUE);
		st = "PosY: " + std::to_string(this->drive->statedata.Y);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 100, 18, BLUE);
		st = "Fai : " + std::to_string(this->drive->statedata.Fi_a);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 130, 18, BLUE);


		st = "Velocity    : " + std::to_string(sqrt(this->drive->movedata.v_X * this->drive->movedata.v_X + this->drive->movedata.v_Y * this->drive->movedata.v_Y));
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 200, 20, RED);
		st = "Velocity_Fai: " + std::to_string(this->drive->movedata.v_Fi_a / 180 * PI);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 230, 18, RED);


		st = "Acceleration: " + std::to_string(this->drive->inputope.temp_acceleration);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 300, 18, RED);


		st = "Angle fl: " + std::to_string(this->drive->wheeldata.delt_fl);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 350, 18, DARKBROWN);
		st = "Angle fr: " + std::to_string(this->drive->wheeldata.delt_fr);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 380, 18, DARKBROWN);
		st = "Angle rl: " + std::to_string(this->drive->wheeldata.delt_rl);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 410, 18, DARKBROWN);
		st = "Angle rr: " + std::to_string(this->drive->wheeldata.delt_rr);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 440, 18, DARKBROWN);



		//改变模式
		if (GuiDropdownBox({ this->panelpos.x + 10, this->panelpos.y + 40,150,25 }, this->data.drivemodename, &this->data.drivemode, this->drapboxopened))
		{
			this->drapboxopened = !this->drapboxopened;

			if (this->data.drivemode == SteeringType::DIAG)
			{
				this->drive->steeringtype = (SteeringType)this->data.drivemode;
				this->drive->turnSteeringType_Direct(this->drive->steeringtype, this->drive->inputope.outWheelRatio());
			}
			else if (this->data.drivemode == SteeringType::LATE)
			{
				if (this->drive->movedata.v_X == 0 && this->drive->movedata.v_Y == 0)
				{
					this->drive->steeringtype = (SteeringType)this->data.drivemode;
					this->drive->turnSteeringType_Direct(this->drive->steeringtype, this->drive->inputope.outWheelRatio());
				}
				else
				{
					this->data.drivemode = this->drive->steeringtype;
					this->isbad_modeset = true;
				}

			}
			else if (this->data.drivemode == SteeringType::ROUN)
			{
				if (this->drive->movedata.v_X == 0 && this->drive->movedata.v_Y == 0)
				{
					this->drive->steeringtype = (SteeringType)this->data.drivemode;
					this->drive->turnSteeringType_Direct(this->drive->steeringtype, this->drive->inputope.outWheelRatio());
				}
				else
				{
					this->data.drivemode = this->drive->steeringtype;
					this->isbad_modeset = true;
				}

			}
			else if (this->data.drivemode == SteeringType::F_ST)
			{
				this->drive->steeringtype = (SteeringType)this->data.drivemode;
				this->drive->turnSteeringType_Direct(this->drive->steeringtype, this->drive->inputope.outWheelRatio());
			}
			else if (this->data.drivemode == SteeringType::A_ST)
			{
				this->drive->steeringtype = (SteeringType)this->data.drivemode;
				this->drive->turnSteeringType_Direct(this->drive->steeringtype, this->drive->inputope.outWheelRatio());
			}



		}


		if (this->isbad_modeset)
		{
			if (GuiMessageBox({ GetRenderWidth() / 2.0f,GetRenderHeight() / 2.0f,400,100 }, "ERROR !", "Try After Car Stopping!", "KNOW"))
			{
				if (this->drive->movedata.v_X == 0 && this->drive->movedata.v_Y == 0)
				{
					this->isbad_modeset = false;
				}
			}
		}




		//档位

		int t = this->drive->gears == -1 ? 0 : 1;
		DrawText("Gears", this->panelpos.x + 10, this->panelpos.y + 480, 16, DARKBLUE);
		if (GuiToggleSlider({ this->panelpos.x + 80, this->panelpos.y + 480,100,16 }, "R;D", &t))
		{
			if (this->drive->movedata.v_X == 0 && this->drive->movedata.v_Y == 0 && this->drive->movedata.v_Fi_a == 0)
			{
				if (t == 0)
				{
					t = -1;
				}

				this->drive->gears = t;
			}
			else
			{
			}

		}




		//自动回正
		GuiSlider({ this->panelpos.x + 110, this->panelpos.y + 510,100,16 }, "ReWheel Rat", std::to_string(this->drive->reWheel_ratio).c_str(),
			&this->drive->reWheel_ratio, 0, 1);



		//跟随车辆
		if (GuiCheckBox({ this->panelpos.x , this->panelpos.y + 550, 20,20 }, "Follow Car", &this->data.is_followcar))
		{
			this->data.is_lookatcar = true;

			if (this->drive->camera == nullptr)
			{
				this->data.is_followcar = false;
				this->data.is_lookatcar = false;
			}
		}
		if (GuiCheckBox({ this->panelpos.x + 120, this->panelpos.y + 550, 20,20 }, "LookAt Car", &this->data.is_lookatcar))
		{
			if (this->drive->camera == nullptr)
			{
				this->data.is_lookatcar = false;
			}

		}

		if (this->data.is_lookatcar)
		{


			this->drive->camera->target.x = this->drive->statedata.X * COORD_ZOOM;
			this->drive->camera->target.z = -this->drive->statedata.Y * COORD_ZOOM;


			if (this->data.is_followcar)
			{
				//SetCameraMode(*this->drive->camera, CameraMode::CAMERA_FIRST_PERSON);
				//this->drive->camera->position.x = 0; 
				//this->drive->camera->position.z = 0;
			}
		}




		//记路径
		if (GuiCheckBox({ this->panelpos.x , this->panelpos.y + 585, 20,20 }, "Record Trace", &this->data.is_tracerecord))
		{
			this->data.countclock = 0;
		}

		if (this->data.is_tracerecord)
		{
			if (++this->data.countclock == 10)
			{
				this->drive->recordTrace();
				this->data.countclock = 0;
			}
		}


		//定速巡航
		if (GuiCheckBox({ this->panelpos.x, this->panelpos.y + 630,20,20 }, "instance-speed", &this->drive->instance_speed))
		{
			this->drive->pressPedal(this->drive->inputope.pedalacc_ratio, 0);
		}
		if (this->drive->instance_speed)
		{
			this->drive->inputope.outAcceleration(
				sqrt(this->drive->movedata.v_X * this->drive->movedata.v_X + this->drive->movedata.v_Y * this->drive->movedata.v_Y), this->drive->movedata.v_Fi_a);
		}



		st = std::to_string(this->drive->inputope.pedalacc_ratio);
		if (GuiSlider({ this->panelpos.x + 40, this->panelpos.y + 660,120,20 }, "ACC", st.c_str(), &this->drive->inputope.pedalacc_ratio, 0, 1))
		{
			this->drive->pressPedal(this->drive->inputope.pedalacc_ratio, 0);

		}

		st = std::to_string(this->drive->inputope.pedalbra_ratio);
		if (GuiSlider({ this->panelpos.x + 40, this->panelpos.y + 690,120,20 }, "BRA", st.c_str(), &this->drive->inputope.pedalbra_ratio, 0, 1))
		{

			this->drive->pressPedal(0, this->drive->inputope.pedalbra_ratio);
		}


		//转向控制
		st = "Steering Angle: " + std::to_string(this->drive->inputope.steering_wheel_angle);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 730, 15, RED);
		if (GuiSlider({ this->panelpos.x + 35, this->panelpos.y + 750,170,26 }, "<-[L]", "[R]->", &this->drive->inputope.steering_wheel_angle, -899.999, 899.999))
		{
			this->drive->turnSteeringWheel(this->drive->inputope.steering_wheel_angle);

		}



		//this->vbasicdata->a + this->vbasicdata->b
		//后轮转向控制
		st = "A_Steering RotPOS: " + std::to_string(this->drive->inputope.rotcenter_distance_A);
		DrawText(st.c_str(), this->panelpos.x + 10, this->panelpos.y + 780, 15, DARKPURPLE);
		if (GuiSlider({ this->panelpos.x + 40, this->panelpos.y + 800,150,16 }, "<-DE", "UP->",
			&this->drive->inputope.rotcenter_distance_A, 0, this->drive->vbasicdata->a + this->drive->vbasicdata->b - 0.001))
		{
			this->drive->setRotateRearWheel(this->drive->inputope.rotcenter_distance_A);

		}


		
		DrawText("Press UP to ACC\nPress DOWN to BRAKE\nPress LEFT to Wheel L\nPress RIGHT to Wheel R\nBLANK to Control Rear Wheel",
			this->panelpos.x , this->panelpos.y + 820, 14, BLACK);




		this->drive->KeyControl(IsKeyDown(KEY_UP), IsKeyDown(KEY_DOWN), IsKeyDown(KEY_LEFT), IsKeyDown(KEY_RIGHT), IsKeyDown(KEY_SPACE));


	}


	if (this->drive->accident != 0)
	{
		if (this->drive->accident == -1)
		{
			if (GuiMessageBox({ GetRenderWidth() / 2.0f,GetRenderHeight() / 2.0f,300,300 }, "ACCIDENT !", "Car Crash!", "KNOW"))
			{
				this->drive->accident = 0;
			}
		}


	}

}

HUDData::HUDData()
	:is_tracerecord(true),is_followcar(true),is_lookatcar(true)
{
}
