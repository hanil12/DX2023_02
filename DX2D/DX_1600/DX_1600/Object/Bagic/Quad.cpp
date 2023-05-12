#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
    _vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

Quad::Quad(wstring srvFile)
{
    _vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");

    _srv = make_shared<SRV>(srvFile);
    _samplerState = make_shared<SamplerState>();

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
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
    _indexBuffer->Set();

    _vs->Set();

    _srv->Set(0);
    _samplerState->Set(0);
    _ps->Set();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::CreateVertices()
{
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = (_srv->GetImageSize().x / WIN_WIDTH) * 0.5f;
    halfSize.y = (_srv->GetImageSize().y / WIN_HEIGHT) * 0.5;

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    temp.color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    temp.uv = { 0.0f, 0.0f };
    _vertices.push_back(temp);  // ������

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.7f, 0.6f, 1.0f, 1.0f);
    temp.uv = { 1.0f, 0.0f };
    _vertices.push_back(temp); // ������ ��

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    temp.uv = { 1.0f,1.0f };
    _vertices.push_back(temp); // ������ �Ʒ�

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    temp.color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    temp.uv = { 0.0f, 1.0f };
    _vertices.push_back(temp); // ���� �Ʒ�

    _indices.push_back(0); 
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}
