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
#include <time.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// DirectXTex
#include "../DirextTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

// Imgui
#include "../ImGUi/imgui.h"
#include "../ImGUi/imgui_impl_win32.h"
#include "../ImGUi/imgui_impl_dx11.h"

// FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib,"Library/FMOD/fmod_vc.lib")

using namespace std;
using namespace DirectX;
using namespace Microsoft::WRL;

// Types
#include "Types.h"

// Framework
#include "Framework/Device/Device.h"

// Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/MyMath.h"

// Utility
#include "Framework/Utility/InputManager.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/tinyxml2.h"
#include "Framework/Utility/Sound.h"

//Render
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/VertexLayOut.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"

// Camera
#include "Framework/Camera/Camera.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"

// TextureMapping
#include "Framework/TextureMapping/SRV.h"
#include "Framework/TextureMapping/SRVManager.h"
#include "Framework/TextureMapping/SamplerState.h"
#include "Framework/TextureMapping/BlendState.h"
#include "Framework/TextureMapping/StateManager.h"

// Animation
#include "Framework/Animation/Action.h"

// Object
#include "Object/Bagic/Quad.h"
#include "Object/Bagic/Sprite.h"
#include "Object/Bagic/Effect.h"
#include "Object/Bagic/EffectManager.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"

extern HWND hWnd;