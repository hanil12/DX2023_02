

float4 VS( float4 pos : POSITION ) : SV_POSITION // Symentic Name... SV -> SystemValue
{
	return pos;
}

float4 PS() : SV_TARGET
{
	return float4(1.0f,1.0f,0.0f,1.0f);
}