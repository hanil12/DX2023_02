#pragma once
class Dun_Bullet
{
public:
	Dun_Bullet();
	~Dun_Bullet();

	void Collider_Update();
	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	bool _isActive = false;
private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _collider;

	Vector2 _dir = Vector2();
	float _speed = 150.0f;
};

