#include "framework.h"
#include "Collider.h"

bool Collider::_isDebugMode = false;
Collider::Collider(Vector2 center)
: _center(center)
, _type(Collider::ColliderType::NONE)
{
	HPEN none = CreatePen(PS_SOLID, 0, RGB(0,0,0));
	HPEN green = CreatePen(PS_SOLID, 1, GREEN);
	HPEN red = CreatePen(PS_SOLID, 1, RED);

	_pens.push_back(none);
	_pens.push_back(green);
	_pens.push_back(red);
}

Collider::~Collider()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Collider::MoveCenter(const Vector2& value)
{
	_center += value;
}

void Collider::SetCenter(const Vector2& value)
{
	_center = value;
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
	// col가 Rect일까 Circle
	switch (col->_type)
	{
	case Collider::ColliderType::NONE:
	{
		// 잘못된 collider 정보입니다.
		return false;
		break;
	}

	case Collider::ColliderType::CIRCLE:
	{
		return IsCollision(dynamic_pointer_cast<CircleCollider>(col));
		break;
	}

	case Collider::ColliderType::RECT:
	{
		return IsCollision(dynamic_pointer_cast<RectCollider>(col));
		break;
	}

	default:
		break;
	}

    return false;
}
