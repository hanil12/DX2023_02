#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	virtual ~VertexShader();

	void CreateBlob(wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	virtual void Set() override;

private:
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3D11InputLayout> _inputLayout;
};

