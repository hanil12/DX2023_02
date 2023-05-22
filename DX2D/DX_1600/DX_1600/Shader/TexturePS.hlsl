
Texture2D map: register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color: COLOR;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp,input.uv);

	return color;
}