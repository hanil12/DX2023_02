#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	shared_ptr<CircleCollider> _circle;
	shared_ptr<CircleCollider> _circleMouse;
	shared_ptr<RectCollider> _rect;
	float _speed = 10.0f;
};

