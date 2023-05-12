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
	shared_ptr<Quad> _quad2;
};

