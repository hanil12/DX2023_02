#include "framework.h"
#include "Line.h"

Line::Line(Vector2 start, Vector2 end)
: _start(start)
, _end(end)
{
	HPEN green = CreatePen(PS_SOLID, 3, GREEN);
	_pens.push_back(green);
	HPEN red = CreatePen(PS_SOLID, 3, RED);
	_pens.push_back(red);
}

Line::~Line()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	MoveToEx(hdc, _start.x, _start.y, nullptr);
	LineTo(hdc, _end.x, _end.y);
}

ColResult_Line Line::IsCollision(shared_ptr<Line> other)
{
	ColResult_Line result;
	result.isCollision = false;
	result.contact = Vector2(0, 0);

	Vector2 a = this->GetVector2();
	Vector2 a1 = other->_start - this->_start;
	Vector2 a2 = other->_end - this->_start;

	Vector2 b = other->GetVector2();
	Vector2 b1 = this->_start - other->_start;
	Vector2 b2 = this->_end - other->_start;

	if (a.IsBetween(a1, a2) && b.IsBetween(b1, b2))
	{
		result.isCollision = true;
		// 충돌지점넣기
		return result;
	}

	result.contact = { -10000.0f, -10000.0f };
	return result;
}
