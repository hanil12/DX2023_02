#pragma once
class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	void SetScale(float value) { _transform->SetScale({value, value}); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	// Matrix 상속 걸려있는 구조에선 Block X
	bool Block(shared_ptr<CircleCollider> movable);

private:
	float _radius;
};

