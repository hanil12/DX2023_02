#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<RectCollider> _rectCollider;
	shared_ptr<RectCollider> _rectCollider2;
	shared_ptr<CircleCollider> _circleCollider;
	shared_ptr<CircleCollider> _circleCollider2;

	Vector2 _circlePos;
};

