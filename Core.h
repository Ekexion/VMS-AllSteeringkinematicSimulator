#pragma once



#include<iostream>

#include<raylib.h>
#include<raymath.h>

#include<raygui.h>




#define ON true

#define GRID_SWITCH ON
#define SHOWFPS_SWITCH ON

#define MSAA 2

const float COORD_ZOOM = 0.1;

//const float v_m_scale = 10;

const unsigned int WINDOW_W = 1680;
const unsigned int WINDOW_H = 945;
const char* const  APPNAME = "AWD-AWS'sMovementSimulator";



const Color BK_COLOR = LIGHTGRAY;



const Color Wheel_Color = DARKBROWN;
const unsigned int Wheel_Sides = 24;//���ٿ��Լ���gpuѹ��������Ⱦ�����½�

const float std_Wheel_height = 0.800;//��̥��
const float std_Wheel_width = 0.300;//��̥��


const Color Body_Color = DARKGREEN;

const float std_Body_height = 1.2;//��
const float std_Body_width = 2;//��
const float std_Body_Lenth = 4;//��


const Color Susp_Color = RED;

const float std_Susp_width = 0.200;//��
const float std_Susp_Lenth = 0.800;//��

const unsigned int Susp_Sides = 12;//���ٿ��Լ���gpuѹ��������Ⱦ�����½�


const Color Trace_Color = YELLOW;


const Color PedalPress_Color = RED;
const Color PedalRelease_Color = DARKBLUE;

const char* const Steering_Wheel_path = "Resourse/SW.png";



const Color Building_Color_IN = GRAY;
const Color Building_Color_SHAPE = ORANGE;

const float Building_H = 20;
