#include "framework.h"
#include "Button.h"

Button::Button(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/ButtonPS.hlsl"));
	_collider = make_shared<RectCollider>(size);

	_transform->SetParent(_collider->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();
	_buttonBuffer->_data.hovered = 0.3f;
	_buttonBuffer->_data.clicked = 0.6f;
}

Button::~Button()
{
}

void Button::Update()
{
	_collider->Update();
	_transform->Update();

	if (_collider->IsCollision(MOUSE_POS))
	{
		_buttonBuffer->_data.state = 1;
		if (KEY_PRESS(VK_LBUTTON))
		{
			_buttonBuffer->_data.state = 2;
			if(_event != nullptr)
				_event();
		}

		_collider->SetRed();
	}
	else
	{
		_buttonBuffer->_data.state = 0;
		_collider->SetGreen();
	}

	_buttonBuffer->Update();
}

void Button::PostRender()
{
	_transform->SetBuffer(0);
	_buttonBuffer->SetPSBuffer(0);
	_quad->Render();
	_collider->Render();
}
