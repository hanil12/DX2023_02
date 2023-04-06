#include "framework.h"
#include "LineCollisionScene.h"

LineCollisionScene::LineCollisionScene()
{
	_line1 = make_shared<Line>(Vector2(0, 0), Vector2(0, 0));
	_line2 = make_shared<Line>(Vector2(100, 500), Vector2(600, 100));

	_circle = make_shared<CircleCollider>(Vector2(0, 0), 5);
}

LineCollisionScene::~LineCollisionScene()
{
}

void LineCollisionScene::Update()
{
	_line1->_end = mousePos;

	ColResult_Line result = _line1->IsCollision(_line2);
	if (result.isCollision)
	{
		_line1->SetRed();
		_line2->SetRed();
	}
	else
	{
		_line1->SetGreen();
		_line2->SetGreen();
	}

	_circle->SetCenter(result.contact);
}

void LineCollisionScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_circle->Render(hdc);
}
