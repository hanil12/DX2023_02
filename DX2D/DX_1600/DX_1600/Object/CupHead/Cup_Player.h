#pragma once
class Cup_Player
{
public:
	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction();
	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void Input();

	shared_ptr<Collider> GetCollider() { return _col; }

private:
	shared_ptr<CircleCollider> _col;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;

	Vector2 _fixedPos;

	float _jumpPower = 0.0f;
};

