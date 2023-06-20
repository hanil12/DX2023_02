#pragma once
class Cup_Bullet
{
public:
	enum State
	{
		INTRO,
		LOOP
	};

	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void Fire(Vector2 startPos, Vector2 dir);
	void EndEvent();

	bool _isActive = false;
private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _curState = INTRO;

	Vector2 _direction;
	float _speed = 450.0f;

};

