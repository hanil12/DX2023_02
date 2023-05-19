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

#define LERP(s,e,t) s + (e - s) * t