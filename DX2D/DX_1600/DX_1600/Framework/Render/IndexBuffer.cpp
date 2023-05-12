#include "framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, UINT count, UINT offset)
: _data(data), _count(count), _offset(offset)
{
	CreateIndexBuffer();
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::CreateIndexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(UINT) * _count;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = _data;

    DEVICE->CreateBuffer(&bd, &initData, _indexBuffer.GetAddressOf());
}

void IndexBuffer::Set()
{
    DC->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, _offset);
}

