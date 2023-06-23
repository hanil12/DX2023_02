#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	shared_ptr<class Cup_Player> _player;
	shared_ptr<class Cup_Boss> _boss;

	shared_ptr<Button> _button;

	shared_ptr<Collider> _col;
	shared_ptr<Quad> _track;
	shared_ptr<Transform> _transform;
};

