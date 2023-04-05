#pragma once
class Line
{
public:
	Line(Vector2 start, Vector2 end) : _start(start), _end(end) {}
	~Line() {}

	void Update();
	void Render(HDC hdc);

public:
	Vector2 _start;
	Vector2 _end;
};

