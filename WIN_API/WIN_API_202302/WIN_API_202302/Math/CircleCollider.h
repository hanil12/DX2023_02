#pragma once
class RectCollider;

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(Vector2 center, float radius);
	virtual ~CircleCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetRadius(float radius);
	const float& GetRadius() { return _radius; }

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

private:
	float _radius = 0;
};

