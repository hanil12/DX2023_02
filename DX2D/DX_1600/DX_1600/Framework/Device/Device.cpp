#include "framework.h"
#include "Device.h"

Device* Device::_instance = nullptr;
Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateDoubleBuffer();
}

Device::~Device()
{
}

void Device::CreateDeviceAndSwapChain()
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // Numerator / Denominator => 화면 프레임 갱식 속도... FPS
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true; // 창모드

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        IN _swapChain.GetAddressOf(),
        IN _device.GetAddressOf(),
        nullptr,
        IN _deviceContext.GetAddressOf()
    );
}

void Device::CreateDoubleBuffer()
{
    ComPtr<ID3D11Texture2D> backBuffer;

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());

    _deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = WIN_WIDTH;
    vp.Height = WIN_HEIGHT;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    _deviceContext->RSSetViewports(1, &vp);
}

void Device::Clear()
{
    FLOAT myColorR = 0.2f;
    FLOAT myColorG = 0.2f;
    FLOAT myColorB = 0.2f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    DC->ClearRenderTargetView(_renderTargetView.Get(), clearColor);
}

void Device::Present()
{
    _swapChain->Present(0, 0);
}
