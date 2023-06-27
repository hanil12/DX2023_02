#pragma once
class MapToolScene : public Scene
{
public:
	MapToolScene();
	virtual ~MapToolScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	shared_ptr<Button> _saveButton;
	shared_ptr<Button> _loadButton;

	vector<shared_ptr<class Cup_Block>> _blocks;
};

