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

class FrameBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT2 maxFrame = {0.0f, 0.0f};
		XMFLOAT2 curFrame = {0.0f, 0.0f};
	};

	FrameBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{

	}
	virtual ~FrameBuffer() {}

	void SetMaxFrame(Vector2 value)
	{
		_data.maxFrame.x = value.x;
		_data.maxFrame.y = value.y;
	}
	void SetCurFrame(Vector2 value)
	{
		_data.curFrame.x = value.x;
		_data.curFrame.y = value.y;
	}

	Data _data;
};