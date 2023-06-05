#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<Quad> _quad1;
	shared_ptr<Transform> _transform1;

	shared_ptr<Quad> _quad2;
	shared_ptr<Transform> _transform2;

	float _angle1 = 0.0f;
	float _angle2 = 0.0f;
};

