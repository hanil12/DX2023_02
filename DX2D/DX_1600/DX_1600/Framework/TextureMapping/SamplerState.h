#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void Set(int slot = 0);

private:
	ComPtr<ID3D11SamplerState> samplerState;
};

