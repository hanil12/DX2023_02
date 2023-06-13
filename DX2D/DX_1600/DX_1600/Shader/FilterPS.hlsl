
Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer FilterBuffer : register(b0)
{
	int selected;
	int value1;
	int value2;
	int value3;

	float2 imageSize;
	float2 radialCenter;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color: COLOR;
	float2 uv : UV;
};

float4 Mosaic(float2 uv)
{
	float x = floor(uv.x * value1); // floor : 평탄화 ... 소수가 들어오면 소수점 뒤를 날린다.
	float y = floor(uv.y * value1);

	float2 temp;
	temp.x = x / value1;
	temp.y = y / value1;

	return map.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
	float4 result = 0;

	if(value2 == 0)
		return map.Sample(samp, uv);

	for (int i = 0; i < value2; i++)
	{
		float divX = (i + 1) / imageSize.x;
		float divY = (i + 1) / imageSize.y;

		result += map.Sample(samp, float2(uv.x + divX, uv.y));
		result += map.Sample(samp, float2(uv.x - divX, uv.y));
		result += map.Sample(samp, float2(uv.x, uv.y + divY));
		result += map.Sample(samp, float2(uv.x, uv.y - divY));
	}

	result /= 4 * value2;

	return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
	[branch]
	if(selected == 0)
		return map.Sample(samp, input.uv);
	else if(selected == 1)
		return Mosaic(input.uv);
	else if(selected == 2)
		return Blur(input.uv);

	return map.Sample(samp, input.uv);
}