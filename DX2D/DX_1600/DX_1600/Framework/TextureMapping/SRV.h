#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

private:
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};

