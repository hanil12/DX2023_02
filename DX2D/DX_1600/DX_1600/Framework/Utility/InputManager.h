#pragma once
#define KEY_MAX 255

class InputManager
{
private:
	enum State
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager();

public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static InputManager* GetInstance()
	{
		if(_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

	void SetMousePos(const Vector2& pos) { _mousePos = pos; }
	const Vector2& GetMousePos() { return _mousePos; }
	Vector2 GetScreenMousePos() { return _mousePos - CENTER; }

private:
	static InputManager* _instance;

	byte _curState[KEY_MAX] = {};
	byte _oldState[KEY_MAX] = {};
	byte _stateMap[KEY_MAX] = {};

	Vector2 _mousePos;
};

