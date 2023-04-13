#pragma once
class CircleCollider;
class RectCollider;

class Collider
{
public:
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider(Vector2 center);
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	void MoveCenter(const Vector2& value);

	void SetCenter(const Vector2& value);
	const Vector2& GetCenter() { return _center; }

	void SetGreen() { _curPenIndex = 1; }
	void SetRed() { _curPenIndex = 2; }

	virtual bool IsCollision(Vector2 pos) abstract;
	bool IsCollision(shared_ptr<Collider> col);
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other) abstract;

	static void DebugModeOnOff() { _isDebugMode = !_isDebugMode; }

protected:
	static bool _isDebugMode;

	vector<HPEN> _pens;
	UINT _curPenIndex = 1;

	Vector2 _center = { 0.0f,0.0f };
	ColliderType _type;
};

