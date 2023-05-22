#include "framework.h"
#include "SolarSystem.h"

#include "../Object/SolarSystem/Planet.h"

SolarSystem::SolarSystem()
{
	_sun = make_shared<Planet>(L"Resource/sun.png", Vector2(0.1f,0.1f), 0.0001f);
	_earth = make_shared<Planet>(L"Resource/earth.png", Vector2(0.07f,0.07f), 0.0001f);
	_moon = make_shared<Planet>(L"Resource/moon.png", Vector2(0.05f,0.05f), 0.0001f);

	_moon->SetParent(_earth->GetRevolution());
	_earth->SetParent(_sun->GetRevolution());

	_moon->SetPosition(Vector2(100,0));
	_earth->SetPosition(Vector2(300,0));
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::Update()
{
	_sun->SetPosition(MOUSE_POS);

	_sun->Update();
	_earth->Update();
	_moon->Update();
}

void SolarSystem::Render()
{
	ADDITIVE->SetState();
	_sun->Render();

	ALPHA->SetState();
	_earth->Render();
	_moon->Render();
}
