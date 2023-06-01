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

    info.direction[0].Normallize();
    info.direction[1].Normallize();

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

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    if(isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    if (isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool RectCollider::OBB_Collision(shared_ptr<RectCollider> other)
{
    OBBRectInfo infoA = GetOBBInfo();
    OBBRectInfo infoB = other->GetOBBInfo();

    Vector2 aToB = infoB.worldPos - infoA.worldPos;

    // n : normal... 길이가 1인 벡터
    // e : edge... 모서리
    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.length[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.length[1];

    Vector2 neb1 = infoB.direction[0];
    Vector2 eb1 = infoB.direction[0] * infoB.length[0];
    Vector2 neb2 = infoB.direction[1];
    Vector2 eb2 = infoB.direction[1] * infoB.length[1];

    // nea1축으로 투영
    float length = abs(nea1.Dot(aToB));
    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1,eb1,eb2);

    if(length > lengthA + lengthB)
        return false;

    // nea2축으로 투영
    length = abs(nea2.Dot(aToB));
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2,eb1,eb2);

    if (length > lengthA + lengthB)
        return false;

    // neb1축으로 투영
    length = abs(neb1.Dot(aToB));
    lengthA = SeparateAxis(neb1, ea1, ea2);
    lengthB = eb1.Length();

    if (length > lengthA + lengthB)
        return false;

    // neb2축으로 투영
    length = abs(neb2.Dot(aToB));
    lengthA = SeparateAxis(neb2, ea1, ea2);
    lengthB = eb2.Length();

    if (length > lengthA + lengthB)
        return false;

    return true;
}

bool RectCollider::OBB_Collision(shared_ptr<CircleCollider> other)
{
    bool check = true;

    OBBRectInfo infoA = GetOBBInfo();

    Vector2 aToB = other->GetTransform()->GetWorldPosition() - infoA.worldPos;

    // n : normal... 길이가 1인 벡터
    // e : edge... 모서리
    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.length[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.length[1];

    float d = sqrt(pow(infoA.length[0],2) + pow(infoA.length[1],2)) + other->GetWorldRadius();

    if(aToB.Length() > d)
        return false;

    float length = abs(aToB.Dot(nea1));
    float lengthA = ea1.Length();
    float lengthB = other->GetWorldRadius();

    if(length > lengthA + lengthB)
        return false;

    length = abs(aToB.Dot(nea2));
    lengthA = ea2.Length();

    if(length > lengthA + lengthB)
        return false;

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

bool RectCollider::AABB_Collision(shared_ptr<RectCollider> other)
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

bool RectCollider::AABB_Collision(shared_ptr<CircleCollider> other)
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