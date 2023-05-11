#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	void Set();

private:
	ComPtr<ID3DBlob>			pixelBlob;
	ComPtr<ID3D11PixelShader>	pixelShader;
};

