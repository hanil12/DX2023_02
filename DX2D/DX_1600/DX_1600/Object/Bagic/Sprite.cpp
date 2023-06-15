#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector2 size)
: _maxFrame(nullptr)
, Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionPS.hlsl");

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _srv.lock()->GetImageSize();
}

Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
: _maxFrame(nullptr)
, Quad(path, size)
{
	// 칸대로 잘 나뉘어져있는 스프라이트가 생성될 경우
	_maxFrame = make_shared<Vector2>(maxFrame);

	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/ActionPS.hlsl");

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _srv.lock()->GetImageSize();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	_actionBuffer->Update();
}

void Sprite::Render()
{
	_actionBuffer->SetPSBuffer(0);
	Quad::Render();
}

void Sprite::SetCurClip(Vector2 frame)
{
	if(_maxFrame == nullptr)
		return;

	Vector2 size;
	size.x = _actionBuffer->_data.imageSize.x / (*_maxFrame).x;
	size.y = _actionBuffer->_data.imageSize.y / (*_maxFrame).y;

	_actionBuffer->_data.startPos.x = frame.x * size.x;
	_actionBuffer->_data.startPos.y = frame.y * size.y;
	_actionBuffer->_data.size = size;
}

void Sprite::SetCurClip(Action::Clip clip)
{
	_actionBuffer->_data.startPos = clip._startPos;
	_actionBuffer->_data.size = clip._size;
}
