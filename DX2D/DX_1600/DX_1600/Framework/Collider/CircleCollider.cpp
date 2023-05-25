#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
: _radius(radius)
, Collider(ColType::CIRCLE)
{
	CreateVertices();
	Collider::CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	Collider::Update();
}

void CircleCollider::Render()
{
	Collider::Render();
}

void CircleCollider::CreateVertices()
{
    Vertex temp;

	float theta = PI * (1.0f / 18.0f);

	for (int i = 0; i < 37; i++)
	{
		temp.pos = XMFLOAT3(_radius * cos(i * theta), _radius * sin(i * theta), 0.0f);
		_vertices.push_back(temp);
	}
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
	float distance = (_transform->GetWorldPosition() - pos).Length();

	return distance < GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}

void CircleCollider::Block(shared_ptr<CircleCollider> movable)
{
	if(!IsCollision(movable))
		return;

	Vector2 moveableCenter = movable->GetTransform()->GetWorldPosition();
	Vector2 blockCenter = GetTransform()->GetWorldPosition();
	Vector2 dir = moveableCenter - blockCenter;
	float scalar = abs((movable->GetWorldRadius() + GetWorldRadius()) - dir.Length());
	dir.Normallize();

	movable->GetTransform()->AddVector2(dir * scalar);
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector2 center1 = _transform->GetWorldPosition();
	Vector2 center2 = other->_transform->GetWorldPosition();

	float distance = (center1 - center2).Length();

	float radius1 = GetWorldRadius();
	float radius2 = other->GetWorldRadius();

	return distance < GetWorldRadius() + other->GetWorldRadius();
}
