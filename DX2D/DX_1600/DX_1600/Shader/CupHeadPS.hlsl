
Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int    isRight;
	int		padding;
}

cbuffer IntBuffer : register(b1)
{
	int value1;
	int value2;
	int value3;
	int value4;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 Mosaic(float2 uv)
{
	float x = floor(uv.x * value2); // floor : 평탄화 ... 소수가 들어오면 소수점 뒤를 날린다.
	float y = floor(uv.y * value2);

	float2 temp;
	temp.x = x / value2;
	temp.y = y / value2;

	return map.Sample(samp, temp);
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (isRight == 0)
		input.uv.x = 1 - input.uv.x;

	input.uv.x = (startPos.x / imageSize.x) + (size.x / imageSize.x) * input.uv.x;
	input.uv.y = (startPos.y / imageSize.y) + (size.y / imageSize.y) * input.uv.y;

	if (value1 == 0)
	{
		return map.Sample(samp, input.uv);
	}

	return Mosaic(input.uv);
}