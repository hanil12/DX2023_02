#pragma once
//#include "../TextureMapping/SRV.h"

class RenderTarget
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	void Set(XMFLOAT4 clearColor = XMFLOAT4(1,1,1,1));

	shared_ptr<class SRV> GetSRV() { return _rtvSRV; }

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

	UINT _width;
	UINT _height;

	ComPtr<ID3D11Texture2D> _rtvTexture;
	ComPtr<ID3D11RenderTargetView> _rtv;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;

	shared_ptr<class SRV> _rtvSRV;
};

