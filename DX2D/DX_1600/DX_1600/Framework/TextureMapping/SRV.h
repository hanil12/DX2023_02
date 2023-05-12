#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

	Vector2 GetImageSize() { return _size; }

private:
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;

	Vector2 _size;
};

