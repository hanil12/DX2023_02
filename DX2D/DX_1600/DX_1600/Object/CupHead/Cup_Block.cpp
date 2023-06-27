#include "framework.h"
#include "Cup_Block.h"

Cup_Block::Cup_Block(Vector2 pos)
{
	_quad = make_shared<Quad>(L"Resource/CupHead/track.png", Vector2(250,50));
	_transform = make_shared<Transform>();

	_collider = make_shared<RectCollider>(Vector2(250,50));

	_transform->SetParent(_collider->GetTransform());
	_collider->SetPosition(pos);
}

Cup_Block::~Cup_Block()
{
}

void Cup_Block::Update()
{
	if(_isActive == false)
		return;

	_collider->Update();
	_transform->Update();
}

void Cup_Block::Render()
{
	if (_isActive == false)
		return;

	_transform->SetBuffer(0);
	_quad->Render();

	_collider->Render();
}
