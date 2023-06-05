#pragma once
#include "Framework/Math/Vector2.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define PI 3.141592
#define GRAV 1.0f

#define CENTER Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define RED			 {1.0f,0.0f,0.0f,1.0f}
#define GREEN		 {0.0f,1.0f,0.0f,1.0f}
#define BLUE		 {0.0f,0.0f,1.0f,1.0f}
#define WHITE		 {1.0f,1.0f,1.0f,1.0f}
#define BLACK		 {0.0f,0.0f,0.0f,1.0f}
#define GREY		 {0.5f,0.5f,0.5f,1.0f}

#define DEVICE	Device::GetInstance()->GetDevice()
#define DC		Device::GetInstance()->GetDC()

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()
#define BLEND StateManager::GetInstance()->GetBlendState()

#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)

#define MOUSE_POS InputManager::GetInstance()->GetMousePos()

#define DELTA_TIME Timer::GetInstance()->GetDeltaTime()

#define ADD_VS(k) ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k) ShaderManager::GetInstance()->AddPS(k)

#define ADD_SRV(k) SRVManager::GetInstance()->Add_SRV(k)

#define LERP(s,e,t) s + (e - s) * t

struct Hit_Result
{
	bool isCollision = false;
	vector<Vector2> contact;
};