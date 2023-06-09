#pragma once
class RectCollider : public Collider
{
private:
	struct AABBRectInfo
	{
		float left = 0.0f;
		float top = 0.0f;
		float right = 0.0f;
		float bottom = 0.0f;
	};

	struct OBBRectInfo
	{
		Vector2 worldPos;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

public:
	RectCollider(Vector2 size);
	virtual ~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	Vector2 GetWorldSize();

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }

	AABBRectInfo GetAABBInfo();
	OBBRectInfo GetOBBInfo();

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;

	// Matrix 상속 걸려있는 구조에서 X
	virtual bool Block(shared_ptr<RectCollider> movable) override;
	virtual bool Block(shared_ptr<class CircleCollider> movable) override;

private:
	virtual bool AABB_Collision(shared_ptr<RectCollider> other) override final;
	virtual bool AABB_Collision(shared_ptr<CircleCollider> other) override final;

	virtual bool OBB_Collision(shared_ptr<RectCollider> other) override final;
	virtual bool OBB_Collision(shared_ptr<CircleCollider> other) override final;

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
	{
		float r1 = abs(separate.Dot(e1));
		float r2 = abs(separate.Dot(e2));

		return r1 + r2;
	}

	Vector2 _size;
};

