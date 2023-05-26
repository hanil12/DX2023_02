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
		Vector2 direction[2]; // ���� ���� ����
		float length[2]; // ���� ���� ����
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
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	// Matrix ��� �ɷ��ִ� �������� X
	bool Block(shared_ptr<RectCollider> movable);
	bool Block(shared_ptr<class CircleCollider> movable);

private:
	Vector2 _size;
};

