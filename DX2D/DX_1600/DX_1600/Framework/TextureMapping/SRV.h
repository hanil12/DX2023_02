#pragma once
class SRV
{
public:
	SRV(ComPtr<ID3D11ShaderResourceView> srv);
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

	Vector2 GetImageSize() { return _size; }

private:
	ComPtr<ID3D11ShaderResourceView> _srv;

	Vector2 _size;
};

