#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	virtual ~DungreedScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class Dun_Player> _player;
};

