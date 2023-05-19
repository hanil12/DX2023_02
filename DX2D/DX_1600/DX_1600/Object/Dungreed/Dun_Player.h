#pragma once
class Dun_Player
{
public:
	Dun_Player();
	~Dun_Player();

	void Update();
	void Render();

	void SetBowAngle();
	const Vector2& GetPos() { return _quad->GetTransform()->GetPos(); }

	void Fire();

private:
	shared_ptr<Quad> _quad;

	shared_ptr<Transform> _bowSlot;
	shared_ptr<Quad> _bow;

	vector<shared_ptr<class Dun_Bullet>> _bullets;
};

