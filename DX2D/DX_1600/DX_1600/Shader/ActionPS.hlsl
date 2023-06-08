
Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int padding[2];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color: COLOR;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	// curFrame (1,0) , (10,8)
	// input.uv.x .. 0 ~ 1
	//                     offset                  뽑아낼 전체 길이   * (0 ~ 1)
	input.uv.x = (startPos.x / imageSize.x) + (size.x / imageSize.x) * input.uv.x;
	input.uv.y = (startPos.y / imageSize.y) + (size.y / imageSize.y) * input.uv.y;

	float4 color = map.Sample(samp, input.uv);

	return color;
}