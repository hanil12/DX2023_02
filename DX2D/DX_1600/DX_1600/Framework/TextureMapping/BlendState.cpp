#include "framework.h"
#include "BlendState.h"

BlendState::BlendState()
{
	_desc.AlphaToCoverageEnable = false;
	_desc.IndependentBlendEnable = false;

	_desc.RenderTarget[0].BlendEnable = false;
	_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Change();
}

BlendState::~BlendState()
{
}

void BlendState::SetState()
{
	float blendFactor[] = {0,0,0,0};
	DC->OMSetBlendState(_state.Get(), blendFactor, 0xffffffff);
}

void BlendState::Alpha()
{
	_desc.RenderTarget[0].BlendEnable = true;
	_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	Change();
}

void BlendState::Additive()
{
	_desc.RenderTarget[0].BlendEnable = true;
	_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	Change();
}

void BlendState::Change()
{
	if(_state != nullptr)
		_state->Release();

	DEVICE->CreateBlendState(&_desc, _state.GetAddressOf());
}
