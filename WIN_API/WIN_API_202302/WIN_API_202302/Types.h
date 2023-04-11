#pragma once
#include "Math/Vector2.h"

// Types
#define PI 3.141592
#define GRAVITY 0.009f

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTER_X 640
#define CENTER_Y 360

#define WHITE		 RGB(255,255,255)
#define RED			 RGB(255,0,0)
#define GREEN		 RGB(0,255,0)
#define BLUE		 RGB(0,0,255)
#define YELLOW		 RGB(255,255,0)
#define CYAN		 RGB(0,255,255)

#define LERP(s,e,t) s + (e - s)*t

struct ColResult_Line
{
	bool isCollision;
	Vector2 contact;
};

static bool isDebugMode = false;