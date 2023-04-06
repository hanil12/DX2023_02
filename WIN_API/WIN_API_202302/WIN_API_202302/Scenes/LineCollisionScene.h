#pragma once
class LineCollisionScene : public Scene
{
public:
	LineCollisionScene();
	virtual ~LineCollisionScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Line> _line1;
	shared_ptr<Line> _line2;

	shared_ptr<CircleCollider> _circle;
};

