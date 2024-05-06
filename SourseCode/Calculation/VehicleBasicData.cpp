#include "VehicleBasicData.h"














InputOperate::InputOperate(float m, float steering_ratio, float power_allo_ratio_f)
    :steering_ratio(steering_ratio),pedalacc_ratio(0),pedalbra_ratio(0) ,is_LATE_flag(false),rotcenter_distance_A(0),
    m(m), steering_wheel_angle(0),temp_acceleration(0), power_allo_ratio_f(power_allo_ratio_f)
{};





float InputOperate::outWheelRatio()
{
    return -this->steering_wheel_angle * this->steering_ratio;
}



float InputOperate::outVelocity_DIAG(const float& deltatime, const float& v_now)
{
    auto v = v_now + deltatime * this->temp_acceleration;

    return  v > small_velocity_except ? v : 0;
}

float InputOperate::outVelocity_LATE(const float& deltatime, const float& v_now)
{
    if (this->temp_acceleration < 0)
    {

        auto v = v_now + deltatime * this->temp_acceleration;

        if (v_now == 0)
        {

            return 0;

        }
        else if (this->is_LATE_flag > 0 && this->outWheelRatio() < 0)
        {

            return -v;
        }
        else if (this->is_LATE_flag < 0 && this->outWheelRatio() >= 0)
        {


            return -v;
        }



        return abs(v) > small_velocity_except ? v : 0;


    }
    else
    {
        if (v_now == 0)
        {

            this->is_LATE_flag = this->outWheelRatio() >= 0 ? 1 : -1;
        }
        else if (this->is_LATE_flag > 0 && this->outWheelRatio() < 0)
        {
            auto v = v_now - deltatime * this->temp_acceleration;

            if ((v > small_velocity_except ? v : 0) == 0)
            {
                this->is_LATE_flag = -1;
                return 0;
            }

            return -v;
        }
        else if (this->is_LATE_flag < 0 && this->outWheelRatio() >= 0)
        {
            auto v = v_now - deltatime * this->temp_acceleration;

            if ((v > small_velocity_except ? v : 0) == 0)
            {
                this->is_LATE_flag = 1;
                return 0;
            }

            return -v;
        }

        auto v = v_now + deltatime * this->temp_acceleration;

        return v > small_velocity_except ? v : 0;
    }


}

float InputOperate::outVelocity_F(const float& deltatime, const float& v_now, const float& beta, const float& delt)
{
    auto v_f = deltatime *  this->temp_acceleration * this->power_allo_ratio_f         * cos( (delt - beta) / 180 * PI);

    auto v_r = deltatime * this->temp_acceleration * (1 - this->power_allo_ratio_f)    * cos(beta / 180 * PI);



    auto v = v_now + v_f + v_r;

    return  v > small_velocity_except ? v : 0;
}



float InputOperate::outVelocity_A(const float& deltatime, const float& v_now, const float& beta, const float& delt_f, const float& delt_r)
{

    auto v_f = deltatime * this->temp_acceleration * this->power_allo_ratio_f * cos((delt_f - beta) / 180 * PI);

    auto v_r = deltatime * this->temp_acceleration * (1 - this->power_allo_ratio_f) * cos((delt_r - beta) / 180 * PI);



    auto v = v_now + v_f + v_r;

    return  v > small_velocity_except ? v : 0;


}






float InputOperate::outVFi_ROUN(const float& deltatime, const float& R, const float& vfi_now)
{

    auto tv = deltatime * this->temp_acceleration / R * 180 / PI;

    if (this->temp_acceleration > 0)
    {


        return  abs(vfi_now + tv) > small_vfi_except ? vfi_now + tv : 0;
    }
    else
    {

        auto ttv = abs(vfi_now + tv) > small_vfi_except ? vfi_now + tv : 0;

        if (ttv < 0 && R>0)
        {
            if (abs(vfi_now) > small_vfi_except)
            {
                return abs(vfi_now + tv) > small_vfi_except ? vfi_now - tv : 0;
            }
            else
            {
                return 0;
            }
        }
        else if (ttv > 0 && R < 0)
        {
            if (abs(vfi_now) > small_vfi_except)
            {
                return abs(vfi_now + tv) > small_vfi_except ? vfi_now - tv : 0;
            }
            else
            {
                return 0;
            }
        }

        return ttv;

    }
    



}





float InputOperate::outAcceleration(const float& v_now, const float& vfi_now)
{
    auto vir_v = v_now + abs(vfi_now / 2) / 180 * PI * this->force.resis_r_ratio/*×¢Òâ£¡£¡£¡*/;

    float drive_force = 0;
    float resis_force = 0;

    if (this->pedalacc_ratio > 0)
    {
        drive_force = this->force.r_acc * this->pedalacc_ratio; 
    }
    else if (this->pedalbra_ratio > 0)
    {
        drive_force = -this->force.r_bra * this->pedalbra_ratio; 
    }

    if (vir_v == 0)
    {
        if (abs(drive_force) < this->force.resis_a)
        {
            resis_force = drive_force;
        }
        else
        {
            resis_force = this->force.resis_a;
        }
        
    }
    else
    {
        resis_force = this->force.resis_a + this->force.resis_b * vir_v * vir_v + this->force.resis_c * vir_v ;//×èÁ¦
    }

 
    this->temp_acceleration =(drive_force - resis_force) / this->m;
    return this->temp_acceleration;
}




VehicleForceModel::VehicleForceModel(float r_acc, float r_bra, float resis_a, float resis_b, float resis_c)
    : r_acc(r_acc), r_bra(r_bra), resis_a(resis_a), resis_b(resis_b),resis_c(resis_c),resis_r_ratio(Resis_R_Ratio)
{
}
