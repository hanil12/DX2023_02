#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
: _size(size)
{
    CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
}

void RectCollider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

void RectCollider::CreateData()
{
    CreateVertices();

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

    _vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

    _transform = make_shared<Transform>();

    _colorBuffer = make_shared<ColorBuffer>();
    SetGreen();
}

void RectCollider::CreateVertices()
{
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = (_size.x) * 0.5f;
    halfSize.y = (_size.y) * 0.5;

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp);  // 왼쪽위

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp);  // 왼쪽위
}
