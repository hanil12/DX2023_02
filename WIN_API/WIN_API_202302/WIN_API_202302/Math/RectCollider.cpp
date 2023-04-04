#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 center, Vector2 size)
: _center(center)
, _size(size)
, _halfSize(size * 0.5f)
{
	HPEN green = CreatePen(PS_SOLID, 1, GREEN);
	HPEN red = CreatePen(PS_SOLID, 1, RED);
	_pens.push_back(green);
	_pens.push_back(red);
}

RectCollider::~RectCollider()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

void RectCollider::Update()
{

}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPenIndex]);

	float left		 = _center.x - _halfSize.x;
	float top		 = _center.y - _halfSize.y;
	float right		 = _center.x + _halfSize.x;
	float bottom	 = _center.y + _halfSize.y;

	Rectangle(hdc, left, top, right, bottom);
}

void RectCollider::MoveCenter(const Vector2& value)
{
	_center += value;
}

void RectCollider::SetCenter(const Vector2& value)
{
	_center = value;
}

void RectCollider::SetSize(const Vector2& size)
{
	_size = size;
	_halfSize = _size * 0.5f;
}

bool RectCollider::IsCollision(Vector2 pos)
{
	return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	return false;
}
