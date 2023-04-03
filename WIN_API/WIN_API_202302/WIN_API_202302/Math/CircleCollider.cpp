#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 center, float radius)
: _center(center)
, _radius(radius)
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
	float left = _center.x - _radius;
	float top = _center.y - _radius;
	float right = _center.x + _radius;
	float bottom = _center.y + _radius;
	Ellipse(hdc, left, top, right, bottom);
}

void CircleCollider::MoveCenter(const Vector2& value)
{
	_center += value;
}

void CircleCollider::SetCenter(const Vector2& value)
{
	_center = value;
}

void CircleCollider::SetRadius(float radius)
{
	_radius = radius;
}
