#pragma once
class EffectScene : public Scene
{
public:
	EffectScene();
	virtual ~EffectScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<Effect> _effect;
};

