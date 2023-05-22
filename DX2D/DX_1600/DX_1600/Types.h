#pragma once
#include "Framework/Math/Vector2.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define PI 3.141592

#define CENTER Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

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

#define LERP(s,e,t) s + (e - s) * t