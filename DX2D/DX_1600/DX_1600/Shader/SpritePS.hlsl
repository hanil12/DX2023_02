
Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer FrameBuffer : register(b0)
{
	float2 maxFrame;
	float2 curFrame;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	// curFrame (1,0) , (10,8)
	// input.uv.x .. 0 ~ 1
	input.uv.x = (input.uv.x + curFrame.x) / maxFrame.x;
	input.uv.y = (input.uv.y + curFrame.y) / maxFrame.y;

	float4 color = map.Sample(samp, input.uv);

	return color;
}