#pragma once
class RectCollider
{
public:
	RectCollider(Vector2 center, Vector2 size);
	~RectCollider();

	void Update();
	void Render(HDC hdc);

	void MoveCenter(const Vector2& value);

	void SetCenter(const Vector2& value);
	const Vector2& GetCenter() { return _center; }

	void SetSize(const Vector2& size);
	const Vector2& GetSize() { return _size; }

	void SetGreen() { _curPenIndex = 0; }
	void SetRed() { _curPenIndex = 1; }

	bool IsCollision(Vector2 pos);
	bool IsCollision(shared_ptr<CircleCollider> other); // 맨나중에
	bool IsCollision(shared_ptr<RectCollider> other);

private:
	vector<HPEN> _pens;
	UINT _curPenIndex = 0;

	Vector2 _center;
	Vector2 _size;
	Vector2 _halfSize;
};

