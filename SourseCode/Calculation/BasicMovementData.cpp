#include "BasicMovementData.h"








float cal_Acceleration(const float& m_, const float& force)
{
    return force / m_;
}

float cal_Velocity(const float& a, const float& v_old, const float& delta_time)
{
    return v_old + a * delta_time;
}



MovementStateData cal_State_Add(const MovementData& in, const float& delta_time)
{
    MovementStateData out{};

    out.X = in.v_X * delta_time;
    out.Y = in.v_Y * delta_time;
    out.Fi_a = in.v_Fi_a * delta_time;

    return out;
}

MovementStateData cal_State_Dir(const MovementStateData& old_state, const MovementData& in, const float& delta_time)
{
    MovementStateData out{};

    out.X = old_state.X + in.v_X * delta_time;
    out.Y = old_state.Y + in.v_Y * delta_time;
    out.Fi_a = old_state.Fi_a + in.v_Fi_a * delta_time;

    return out;
}



float cal_Beta_F(const float& a, const float& b, const float& delt_f)
{
    if (abs(delt_f) == 90 )
    {
        return delt_f;
    }

    return atan(a / (a + b) * tan(delt_f / 180 * PI)) * 180 / PI;
}



float cal_Beta_A(const float& a, const float& b, const float& rotcenter_distance_A, const float& delt_f, const float& delt_r)
{
    float d_f = delt_f / 180 * PI,  d_r = delt_r / 180 * PI;

    if (rotcenter_distance_A == 0)
    {
        return cal_Beta_F(a,b, delt_f);
    }

    if (rotcenter_distance_A == b)
    {
        return 0;
    }

    if (rotcenter_distance_A < b)
    {
        return  -atan((b - rotcenter_distance_A) / rotcenter_distance_A * tan(d_r)) * 180 / PI;
    }

    if (rotcenter_distance_A > b)
    {
        return - atan(((a + b) - rotcenter_distance_A) / rotcenter_distance_A * tan(d_f)) * 180 / PI;
    }
}



void cal_Delt_Akeman(float& left_delt, float& right_delt, const float& delt_virtual, const float& L, const float& B)
{
    auto R = L / tan(delt_virtual / 180 * PI);

    left_delt = atan(L /( R - B / 2)) * 180 /PI;

    right_delt = atan(L / (R + B / 2)) * 180 / PI;

}



void cal_Delt_Akeman_A(float& inr_delt_f, float& outr_delt_f, float& inr_delt_r, float& outr_delt_r, const float& rotcenter_distance_A, const float& delt_virtual_f, const float& delt_virtual_r, const float& L, const float& B)
{

    cal_Delt_Akeman(inr_delt_f, outr_delt_f, delt_virtual_f, L - rotcenter_distance_A, B);

    if (rotcenter_distance_A != 0)
    {
        cal_Delt_Akeman( outr_delt_r,inr_delt_r, delt_virtual_r, rotcenter_distance_A, B);
    }
    else
    {
        inr_delt_r = 0;
        outr_delt_r = 0;
    }


}




float cal_DeltRear_A(const float& rotcenter_distance_A, const float& delt_f, const float& L)
{
    auto Rv = (L - rotcenter_distance_A) / tan(delt_f / 180 * PI);

    auto delt_abs = - atan(rotcenter_distance_A / Rv) * 180 /PI;


    return delt_abs;
}




MovementData cal_FST(const float& v, const float& delt, const float& beta, const float& fi, const float& L)
{
    auto d_delt = delt / 180 * PI;
    auto d_beta = beta / 180 * PI;
    auto d_fi = fi / 180 * PI;

    MovementData out{};

    out.v_X = v * cos(d_fi + d_beta);
    out.v_Y = v * sin(d_fi + d_beta);

    out.v_Fi_a = v / L * tan(d_delt) * cos(d_beta) * (180 /PI);

    return out;
}





MovementData cal_AST(const float& v, const float& delt_f, const float& delt_r, const float& beta, const float& fi, const float& L)
{
    auto d_delt_f = delt_f / 180 * PI;
    auto d_delt_r = delt_r / 180 * PI;

    auto d_beta = beta / 180 * PI;
    auto d_fi = fi / 180 * PI;

    MovementData out{};

    out.v_X = v * cos(d_fi + d_delt_r + d_beta);
    out.v_Y = v * sin(d_fi + d_delt_r + d_beta);

    out.v_Fi_a = v / L * sin(d_delt_f - d_delt_r) / cos(d_delt_f) * cos(d_beta) * (180 / PI);

    return out;
}




MovementData cal_DIAG(const float& sita, const float& v)
{
    float sita_r = sita / 180 * PI;

    MovementData out{};

    out.v_X = cos(sita_r) * v;
    out.v_Y = sin(sita_r) * v;
    out.v_Fi_a = 0;

    return out;
}



MovementData cal_LATE(const float& sita, const float& v)
{
    float sita_r = sita / 180 * PI;

    MovementData out{};

    out.v_X = cos(sita_r) * v;
    out.v_Y = sin(sita_r) * v;
    out.v_Fi_a = 0;

    return out;
}



MovementData cal_ROUN(const float& v_fi)
{
    MovementData out{};

    out.v_X = 0;
    out.v_Y = 0;
    out.v_Fi_a = v_fi;

    return out;
}



MovementStateData::MovementStateData(const MovementStateData& in)
    :X(in.X),Y(in.Y),Fi_a(in.Fi_a)
{
}

MovementData::MovementData(const MovementData& in)
    :v_X(in.v_X),v_Y(in.v_Y),v_Fi_a(in.v_Fi_a)
{
}

WheelMovementData::WheelMovementData(const WheelMovementData& in)
    :delt_fl(in.delt_fl), delt_fr(in.delt_fr), delt_rl(in.delt_rl), delt_rr(in.delt_rr)
{
}



