#include "framework.h"
#include "Collider.h"

Collider::Collider(ColType type)
: _type(type)
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
	_transform->Update();
}

void Collider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

void Collider::CreateData()
{
	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

	_vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

	_transform = make_shared<Transform>();

	_colorBuffer = make_shared<ColorBuffer>();
	SetGreen();
}

bool Collider::IsCollision(shared_ptr<Collider> other, bool isObb)
{
	switch (other->_type)
	{
	case Collider::ColType::NONE:
		return false;
	case Collider::ColType::CIRCLE:
	{
		auto circle = dynamic_pointer_cast<CircleCollider>(other);
		return IsCollision(circle, isObb);
	}
	case Collider::ColType::RECT:
	{
		auto rect = dynamic_pointer_cast<RectCollider>(other);
		return IsCollision(rect, isObb);
	}
	default:
		return false;
	}
}

bool Collider::Block(shared_ptr<Collider> other)
{
	switch (other->_type)
	{
	case Collider::ColType::NONE:
		return false;
	case Collider::ColType::CIRCLE:
	{
		auto circle = dynamic_pointer_cast<CircleCollider>(other);
		return Block(circle);
	}
	case Collider::ColType::RECT:
	{
		auto rect = dynamic_pointer_cast<RectCollider>(other);
		return Block(rect);
	}
	default:
		return false;
	}
}
