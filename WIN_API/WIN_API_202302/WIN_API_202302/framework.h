// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>

using namespace std;

#include "Types.h"

// Math
#include "Math/Vector2.h"
#include "Math/Line.h"
#include "Math/Collider.h"
#include "Math/CircleCollider.h"
#include "Math/RectCollider.h"

// Object
#include "Object/Cannon/Bullet.h"
#include "Object/Cannon/Cannon.h"

#include "Object/Maze/MazeBlock.h"
#include "Object/Maze/Maze.h"

// Scene
#include "Scenes/Scene.h"

// Program
#include "Program/Program.h"

extern Vector2 mousePos;
extern HWND hWnd;
extern bool isDebugMode;