#pragma once
class ActionScene : public Scene
{
public:
	ActionScene();
	virtual ~ActionScene();

	virtual void Update() override;
	virtual void Render() override;

	void CreateAction();

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
	shared_ptr<Transform> _transform;
};

