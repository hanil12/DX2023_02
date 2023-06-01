#pragma once
class ShaderManager
{
public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new ShaderManager();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static ShaderManager* GetInstance()
	{
		if(_instance != nullptr)
			return _instance;

		return nullptr;
	}

	shared_ptr<VertexShader> AddVS(wstring path);
	shared_ptr<PixelShader> AddPS(wstring path);

private:
	ShaderManager();
	~ShaderManager();

	static ShaderManager* _instance;

	unordered_map<wstring, shared_ptr<Shader>> _shaderMap;
};

