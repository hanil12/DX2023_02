#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	shared_ptr<Collider> _circle;
	shared_ptr<Collider> _circleMouse;
	shared_ptr<Collider> _rect;
	shared_ptr<Collider> _rectMouse;
	float _speed = 10.0f;
};

