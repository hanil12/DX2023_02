#pragma once
class Cup_Boss
{
public:
	enum State
	{
		INTRO,
		LOOP,
		END,
		DEAD
	};

	Cup_Boss();
	~Cup_Boss();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void TakeDamage(int amount);

private:
	int _hp;
	bool _isActive;

	State _state = State::INTRO;

	shared_ptr<IntBuffer> _intBuffer;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _collider;
};

