#pragma once
class Vector2
{
public:
    Vector2() : x(0.0f), y(0.0f) {}

    Vector2(float x, float y) : x(x), y(y) {}

    ~Vector2() {}

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(this->x + other.x, this->y + other.y);
    }
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(this->x - other.x, this->y - other.y);
    }
    Vector2 operator*(const float& value) const
    {
        return Vector2(this->x * value, this->y * value);
    }
    Vector2& operator+=(const Vector2& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }
    Vector2& operator-=(const Vector2& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    float Distance() const
    {
        return sqrtf(powf(this->x, 2) + powf(this->y, 2));
    }
    float Distance(const Vector2& other) const
    {
        float resultX = x - other.x;
        float resultY = y - other.y;

        return sqrtf(powf(resultX, 2) + powf(resultY, 2));
    }
    float Dot(const Vector2& other) const
    {
        return (this->x * other.x) + (this->y * other.y);
    }
    float Cross(const Vector2& other) const
    {
        return (this->x * other.y) - (other.x * this->y);
    }
    void Normallize()
    {
        this->x /= Distance();
        this->y /= Distance();
    }
    Vector2 NormalVector2() const
    {
        Vector2 result;
        result.x = this->x / Distance();
        result.y = this->y / Distance();

        return result;
    }

public:
    float x;
    float y;
};

