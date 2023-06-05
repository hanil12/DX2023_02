#include "framework.h"
#include "Planet.h"

Planet::Planet(wstring file, Vector2 scale, float angle)
: _angle(angle)
, _revolutionAngle(_angle * 0.5f)
{
	_quad = make_shared<Quad>(file);
	_transform->SetScale(scale);

	_revolution = make_shared<Transform>();
}

Planet::~Planet()
{
}

void Planet::Update()
{
	_transform->AddAngle(_angle);

	_revolution->SetPosition(_transform->GetPos());
	_revolution->AddAngle(_revolutionAngle);

	_transform->Update();
	_revolution->Update();
}

void Planet::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
}
