#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	// 상수 버퍼를 이용할 때 한가지 규칙
	// 16바이트 배수를 무조건 지켜야한다.
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

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color = {1,1,1,1};
	};

	ColorBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~ColorBuffer() {}

	void SetColor(XMFLOAT4 value) { _data.color = value; }

	Data _data;
};