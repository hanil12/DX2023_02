#include "framework.h"
#include "Planet.h"

Planet::Planet(wstring file, Vector2 scale, float angle)
: _angle(angle)
, _revolutionAngle(_angle * 0.5f)
{
	_quad = make_shared<Quad>(file);
	_quad->GetTransform()->SetScale(scale);

	_revolution = make_shared<Transform>();
}

Planet::~Planet()
{
}

void Planet::Update()
{
	_quad->GetTransform()->AddAngle(_angle);

	_revolution->SetPosition(_quad->GetTransform()->GetPos());
	_revolution->AddAngle(_revolutionAngle);

	_quad->Update();
	_revolution->Update();
}

void Planet::Render()
{
	_quad->Render();
}
