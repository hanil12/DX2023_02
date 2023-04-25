#include "framework.h"
#include "Vector2.h"

bool Vector2::operator==(const Vector2& other) const
{
    if(abs(x - other.x) < 0.001f && abs(y - other.y) < 0.001f)
        return true;
    return false;
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !this->operator==(other);
}

bool Vector2::operator<(const Vector2& other) const
{
    if (y != other.y)
    {
        return y < other.y;
    }

    return x < other.x;
}

bool Vector2::operator>(const Vector2& other) const
{
    if (y != other.y)
    {
        return y > other.y;
    }

    return x > other.x;
}

int Vector2::MahattanDistance(const Vector2& other) const
{
    return int(abs(x - other.x) + abs(y - other.y));
}

bool Vector2::IsBetween(Vector2 v1, Vector2 v2)
{
    float cross1 = v1.Cross(*this);
    float cross2 = v2.Cross(*this);

    if ((cross1 * cross2) < 0.0f)
        return true;

    return false;
}
