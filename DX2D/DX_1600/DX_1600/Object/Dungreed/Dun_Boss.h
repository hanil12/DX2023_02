#pragma once
class Dun_Boss
{
public:
	Dun_Boss();
	~Dun_Boss();

	void Collider_Update();
	void Update();
	void Render();

	void SetPostion(Vector2 pos) { _collider->SetPosition(pos); }

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	void Damaged(int amount);

	bool _isActive;
private:
	shared_ptr<CircleCollider> _collider;

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	int _hp = 30;
};

