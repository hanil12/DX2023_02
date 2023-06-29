#include "framework.h"
#include "RenderTarget.h"
#include "../TextureMapping/SRV.h"

RenderTarget::RenderTarget(UINT width, UINT height)
: _width(width), _height(height)
{
	CreateRTVTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
}

void RenderTarget::Set(XMFLOAT4 clearColor)
{
	DC->OMSetRenderTargets(1, _rtv.GetAddressOf(), nullptr);

	DC->ClearRenderTargetView(_rtv.Get(), (float*)&clearColor);
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = _width;
	desc.Height = _height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

	DEVICE->CreateTexture2D(&desc, nullptr, _rtvTexture.GetAddressOf());
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(_rtvTexture.Get(), &desc, _rtv.GetAddressOf());
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = 1;

	DEVICE->CreateShaderResourceView(_rtvTexture.Get(), &desc, _shaderResourceView.GetAddressOf());

	_rtvSRV = make_shared<SRV>(_shaderResourceView);
}
