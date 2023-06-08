#pragma once
class Vector2 : public XMFLOAT2
{
public:
    Vector2() : XMFLOAT2() {}

    Vector2(float x, float y) : XMFLOAT2(x,y) {}

    Vector2(int x, int y) : XMFLOAT2(((float)x), ((float)y)) {}

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

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    bool operator<(const Vector2& other) const;
    bool operator>(const Vector2& other) const;

    float Length() const
    {
        return sqrtf(powf(this->x, 2) + powf(this->y, 2));
    }
    float Distance(const Vector2& other) const
    {
        float resultX = x - other.x;
        float resultY = y - other.y;

        return sqrtf(powf(resultX, 2) + powf(resultY, 2));
    }
    float Angle() const;

    int MahattanDistance(const Vector2& other) const;
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
        // #TODO ¹Ù²ã¾ßÇÔ
        this->x /= Length();
        this->y /= Length();
    }
    Vector2 NormalVector2() const
    {
        Vector2 result;
        result.x = this->x / Length();
        result.y = this->y / Length();

        return result;
    }

    bool IsBetween(Vector2 v1, Vector2 v2);
};

