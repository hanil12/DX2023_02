#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data,UINT count, UINT offset = 0);
	~IndexBuffer();

	void CreateIndexBuffer();

	void Set();

private:
	ComPtr<ID3D11Buffer> _indexBuffer;

	void* _data = nullptr;

	UINT _count = 0;
	UINT _offset = 0;
};

