#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	virtual ~DungreedScene();

	virtual void Collider_Update() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class Dun_Boss> _boss;
	shared_ptr<class Dun_Player_Advanced> _player;
	shared_ptr<RectCollider> _floor;
};

