
Texture2D map: register(t0);
SamplerState samp : register(s0);

cbuffer ButtonBuffer : register(b0)
{
	int state;
	float hovered;
	float clicked;
	float padding;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color: COLOR;
	float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = map.Sample(samp,input.uv);

	[branch]
	if(state == 0)
		return color;
	else if (state == 1)
	{
		color.x -= hovered;
		color.y -= hovered;
		color.z -= hovered;

		return color;
	}
	else if (state == 2)
	{
		color.x -= clicked;
		color.y -= clicked;
		color.z -= clicked;

		return color;
	}

	return color;
}