#pragma once
class Dun_Player
{
public:
	Dun_Player();
	virtual ~Dun_Player();

	virtual void Update() abstract;
	virtual void Render();

	void SetBowAngle();

	virtual void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	virtual void Move(Vector2 movePos) { _transform->AddVector2(movePos); }
	virtual const Vector2& GetPos() { return _transform->GetPos(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void Fire();

protected:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _bowSlot;

	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _bowTrans;

	vector<shared_ptr<class Dun_Bullet>> _bullets;
};

