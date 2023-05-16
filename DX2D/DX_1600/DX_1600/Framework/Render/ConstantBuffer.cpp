#include "framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
: _data(data)
, _dataSize(dataSize)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = _dataSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = _data;

	DEVICE->CreateBuffer(&bd, &initData, _buffer.GetAddressOf());
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Update()
{
	DC->UpdateSubresource(_buffer.Get(), 0, nullptr, _data, 0 ,0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	DC->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	DC->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}
