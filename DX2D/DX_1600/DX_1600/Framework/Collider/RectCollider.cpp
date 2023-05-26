#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
: _size(size)
, Collider(ColType::RECT)
{
    CreateVertices();
    Collider::CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::Render()
{
    Collider::Render();
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

Vector2 RectCollider::GetWorldSize()
{
    Vector2 temp;
    temp.x = _size.x * _transform->GetWorldScale().x;
    temp.y = _size.y * _transform->GetWorldScale().y;

    return temp;
}

RectCollider::AABBRectInfo RectCollider::GetAABBInfo()
{
    AABBRectInfo result;
    result.left = _transform->GetWorldPosition().x - GetWorldSize().x * 0.5f;
    result.top = _transform->GetWorldPosition().y + GetWorldSize().y * 0.5f;
    result.right = _transform->GetWorldPosition().x + GetWorldSize().x * 0.5f;
    result.bottom = _transform->GetWorldPosition().y - GetWorldSize().y * 0.5f;

    return result;
}

RectCollider::OBBRectInfo RectCollider::GetOBBInfo()
{
    OBBRectInfo info;

    info.worldPos = _transform->GetWorldPosition();

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix,_transform->GetMatrix());

    info.direction[0] = { matrix._11, matrix._12 };
    info.direction[1] = { matrix._21, matrix._22 };

    info.length[0] = GetWorldSize().x * 0.5f;
    info.length[1] = GetWorldSize().y * 0.5f;

    return info;
}

bool RectCollider::IsCollision(const Vector2& pos)
{
    AABBRectInfo info = GetAABBInfo();

    if(pos.x > info.right || pos.x < info.left)
        return false;
    if(pos.y > info.top || pos.y < info.bottom)
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    AABBRectInfo info = GetAABBInfo();

    Vector2 leftTop = Vector2(info.left, info.top);
    Vector2 leftBottom = Vector2(info.left, info.bottom);
    Vector2 rightTop = Vector2(info.right, info.top);
    Vector2 rightBottom = Vector2(info.right, info.bottom);

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom) ||
        other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;

    if (info.right > other->GetTransform()->GetWorldPosition().x && info.left < other->GetTransform()->GetWorldPosition().x)
    {
        if (info.top + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().y
            && info.bottom - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().y)
            return true;
    }
    if (info.bottom < other->GetTransform()->GetWorldPosition().y && info.top > other->GetTransform()->GetWorldPosition().y)
    {
        if (info.left - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().x
            && info.right + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().x)
            return true;
    }

    return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = other->GetTransform()->GetWorldPosition();
    Vector2 distance = (this->GetWorldSize() + other->GetWorldSize()) * 0.5f;
    if (abs(center1.x - center2.x) > distance.x)
        return false;
    else if (abs(center1.y - center2.y) > distance.y)
        return false;
    else
        return true;
}

bool RectCollider::Block(shared_ptr<RectCollider> movable)
{
    if(!IsCollision(movable))
        return false;

    Vector2 dir = movable->GetTransform()->GetWorldPosition() - _transform->GetWorldPosition();
    Vector2 sum = movable->GetWorldSize() * 0.5f + GetWorldSize() * 0.5f;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = movable->GetTransform()->GetPos();

    dir.Normallize();
    if (overlap.x > overlap.y)
    {
        if(dir.y < 0.0f)
            dir.y = -1.0f;
        else if(dir.y > 0.0f)
            dir.y = 1.0f;

        fixedPos.y += dir.y * overlap.y;
    }
    else
    {
        if (dir.x < 0.0f)
            dir.x = -1.0f;
        else if (dir.x > 0.0f)
            dir.x = 1.0f;

        fixedPos.x += dir.x * overlap.x;
    }

    movable->GetTransform()->SetPosition(fixedPos);

    return true;
}

bool RectCollider::Block(shared_ptr<CircleCollider> movable)
{
    if (!IsCollision(movable))
        return false;

    Vector2 virtualHalfSize = Vector2(movable->GetWorldRadius(), movable->GetWorldRadius());
    Vector2 dir = movable->GetTransform()->GetWorldPosition() - _transform->GetWorldPosition();
    Vector2 sum = virtualHalfSize + GetWorldSize() * 0.5f;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = movable->GetTransform()->GetPos();

    dir.Normallize();
    if (overlap.x > overlap.y)
    {
        if (dir.y < 0.0f)
            dir.y = -1.0f;
        else if (dir.y > 0.0f)
            dir.y = 1.0f;

        fixedPos.y += dir.y * overlap.y;
    }
    else
    {
        if (dir.x < 0.0f)
            dir.x = -1.0f;
        else if (dir.x > 0.0f)
            dir.x = 1.0f;

        fixedPos.x += dir.x * overlap.x;
    }

    movable->GetTransform()->SetPosition(fixedPos);

    return true;
}