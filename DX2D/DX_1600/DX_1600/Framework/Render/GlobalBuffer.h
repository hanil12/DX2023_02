#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	// ��� ���۸� �̿��� �� �Ѱ��� ��Ģ
	// 16����Ʈ ����� ������ ���Ѿ��Ѵ�.
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{

	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		value = XMMatrixTranspose(value);
		_data.matrix = value;
	}

	Data _data;
};