#include "framework.h"
#include "ShaderManager.h"

ShaderManager* ShaderManager::_instance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

shared_ptr<VertexShader> ShaderManager::AddVS(wstring path)
{
	if(_shaderMap.count(path) != 0)
		return dynamic_pointer_cast<VertexShader>(_shaderMap[path]);

	shared_ptr<VertexShader> vs = make_shared<VertexShader>(path);
	_shaderMap[path] = vs;

	return vs;
}

shared_ptr<PixelShader> ShaderManager::AddPS(wstring path)
{
	if (_shaderMap.count(path) != 0)
		return dynamic_pointer_cast<PixelShader>(_shaderMap[path]);

	shared_ptr<PixelShader> ps = make_shared<PixelShader>(path);
	_shaderMap[path] = ps;

	return ps;
}
