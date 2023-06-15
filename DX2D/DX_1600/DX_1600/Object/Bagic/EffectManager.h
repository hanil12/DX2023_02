#pragma once
class EffectManager
{
private:
	EffectManager();
	~EffectManager();

public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new EffectManager();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static EffectManager* GetInstance()
	{
		if(_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();

	vector<shared_ptr<Effect>>& GetEffects(string name) { return _effectTable[name]; }

	void AddEffect(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.03f, Action::Type type = Action::Type::END);

	void Play(string name, Vector2 pos);

private:
	UINT _poolCount = 30;

	unordered_map<string, vector<shared_ptr<Effect>>> _effectTable; 

	static EffectManager* _instance;
};

