#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
	CreateBlob(file);
	CreateInputLayout();
	CreateVertexShader();
}

VertexShader::~VertexShader()
{
}

void VertexShader::CreateBlob(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	D3DCompileFromFile(file.c_str(), nullptr, nullptr, "VS", "vs_5_0", flags, 0, _blob.GetAddressOf(), nullptr);
}

void VertexShader::CreateInputLayout()
{
    D3D11_INPUT_ELEMENT_DESC layOut[] =
    {
        {
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        },
        {
            "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        },
        {
            "UV", 0, DXGI_FORMAT_R32G32_FLOAT,0,28,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        }
    };

    UINT layoutSize = ARRAYSIZE(layOut);
    DEVICE->CreateInputLayout(layOut, layoutSize, _blob->GetBufferPointer(), _blob->GetBufferSize(), _inputLayout.GetAddressOf());

}

void VertexShader::CreateVertexShader()
{
    DEVICE->CreateVertexShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
}

void VertexShader::Set()
{
    DC->IASetInputLayout(_inputLayout.Get());
    DC->VSSetShader(_vertexShader.Get(), nullptr, 0);
}
