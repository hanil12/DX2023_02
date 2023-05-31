#pragma once
class Dun_Player
{
public:
	Dun_Player();
	virtual ~Dun_Player();

	virtual void Update() abstract;
	virtual void Render();

	void SetBowAngle();

	virtual void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	virtual void Move(Vector2 movePos) { _quad->GetTransform()->AddVector2(movePos); }
	virtual const Vector2& GetPos() { return _quad->GetTransform()->GetPos(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void Fire();

protected:
	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bowSlot;
	shared_ptr<Quad> _bow;

	vector<shared_ptr<class Dun_Bullet>> _bullets;
};

