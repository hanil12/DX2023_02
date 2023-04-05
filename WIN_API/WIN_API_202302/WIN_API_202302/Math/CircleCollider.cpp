#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 center, float radius)
: Collider(center)
, _radius(radius)
{
	_type = Collider::ColliderType::CIRCLE;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
}

void CircleCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPenIndex]);

	float left = _center.x - _radius;
	float top = _center.y - _radius;
	float right = _center.x + _radius;
	float bottom = _center.y + _radius;
	Ellipse(hdc, left, top, right, bottom);
}

void CircleCollider::SetRadius(float radius)
{
	_radius = radius;
}

bool CircleCollider::IsCollision(Vector2 pos)
{
	float distance = (_center - pos).Length();

	return distance < _radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	float distance = (_center - other->GetCenter()).Length();
	float sum = _radius + other->GetRadius();

	return distance < sum;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}
