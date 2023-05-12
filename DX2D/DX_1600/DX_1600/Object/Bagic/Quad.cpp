#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");
}

Quad::Quad(wstring srvFile)
{
    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");

    _srv = make_shared<SRV>(srvFile);
    _samplerState = make_shared<SamplerState>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
}

void Quad::Render()
{
    _vertexBuffer->Set(0);

    _vs->Set();

    _srv->Set(0);
    _samplerState->Set(0);
    _ps->Set();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DC->Draw(_vertices.size(), 0);
}

void Quad::CreateVertices()
{
    Vertex temp;
    temp.pos = XMFLOAT3(-0.5, 0.5f, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 0.0f, 0.0f };
    _vertices.push_back(temp);  // 왼쪽위

    temp.pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
    temp.color = XMFLOAT4(0.7f, 0.6f, 1.0f, 1.0f);
    temp.uv = { 1.0f, 0.0f };
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 1.0f,1.0f };
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 0.0f,0.0f };
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 1.0f, 1.0f };
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);
    temp.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    temp.uv = { 0.0f, 1.0f };
    _vertices.push_back(temp); // 왼쪽 아래
}
