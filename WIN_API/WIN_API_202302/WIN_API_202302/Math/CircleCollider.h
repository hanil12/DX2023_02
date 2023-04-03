#pragma once
class CircleCollider
{
public:
	CircleCollider(Vector2 center, float radius);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	void MoveCenter(const Vector2& value);

	void SetCenter(const Vector2& value);
	const Vector2& GetCenter() { return _center; }

	void SetRadius(float radius);
	const float& GetRadius() { return _radius; }

private:
	Vector2 _center = { 0.0f,0.0f };
	float _radius = 0;
};

