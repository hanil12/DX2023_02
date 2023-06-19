#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		JUMP,
		RUN,
		ATTACK
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);
	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void Input();
	void Jump();
	void Move(Vector2 dir) { dir.Normallize(); _col->GetTransform()->AddVector2(dir * DELTA_TIME * _speed); }
	void Attack();

	void SetAction(State state);
	void SetGrounded() { _isFalling = false; }

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

	shared_ptr<Collider> GetCollider() { return _col; }

private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;

	shared_ptr<IntBuffer> _intBuffer;
	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	Vector2 _fixedPos;

	State _oldState = State::IDLE;
	State _curState = State::IDLE;

	float _speed = 450.0f;
	float _jumpPower = 0.0f;

	bool _isFalling = true;
	bool _isAttack = false;

	shared_ptr<class Cup_Bullet> bullet;
};

