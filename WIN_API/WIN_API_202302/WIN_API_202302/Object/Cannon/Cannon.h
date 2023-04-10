#pragma once
class Cannon
{
public:
	Cannon(Vector2 pos);
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Angle();
	void Fire();

	void CheckAttack();

	void SetTurn(bool isControll) { _isControlled = isControll;}
	void SetTarget(shared_ptr<Cannon> target) { _target = target; }

	shared_ptr<Collider> GetCollider() {return _body; }
	vector<shared_ptr<Bullet>>& GetBullets() { return _bullets;}

private:
	bool _isControlled = false;
	bool _isActive = false;

	float _muzzleLength = 100.0f;
	float _muzzleAngle = 0.0f;
	Vector2 _muzzleDir = Vector2(1.0f, 0.0f);

	// ������Ʈ ���� (��ǰ ���� ����) => ���꼺�� ����
	shared_ptr<Collider> _body;
	shared_ptr<Line> _muzzle;

	vector<shared_ptr<Bullet>> _bullets;

	weak_ptr<Cannon> _target;
};

