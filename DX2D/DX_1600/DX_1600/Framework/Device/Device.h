#pragma once
class Device
{
public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static Device* GetInstance()
	{
		if(_instance != nullptr)
			return _instance;
		return nullptr;
	}

	ComPtr<ID3D11Device> GetDevice() { return _device;}
	ComPtr<ID3D11DeviceContext> GetDC() { return _deviceContext; }

	void Clear();
	void Present();

	void SetMainRenderTarget();

private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateDoubleBuffer();

	static Device* _instance;

	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;
	ComPtr<IDXGISwapChain>			_swapChain;
	ComPtr<ID3D11RenderTargetView>	_renderTargetView;
};

