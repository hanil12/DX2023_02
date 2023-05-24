
cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
};

float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}