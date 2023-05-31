#pragma once
#include "Dun_Player.h"

class Dun_Player_Advanced : public Dun_Player
{
public:
	Dun_Player_Advanced();
	virtual ~Dun_Player_Advanced();

	void Collider_Update();
	virtual void Update() override;
	virtual void Render() override;

	virtual void SetPosition(Vector2 pos) override { _collider->GetTransform()->SetPosition(pos); }
	virtual void Move(Vector2 movePos) override { _collider->GetTransform()->AddVector2(movePos); }
	virtual const Vector2& GetPos() override { return _collider->GetTransform()->GetPos(); }	void Input();

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

	void Falling();

	void SetFalling(bool value) { _isFalling = value; }
private:
	float _speed = 200.0f;
	Vector2 _fallingVec;
	bool _isFalling = true;

	shared_ptr<CircleCollider> _collider;
};

