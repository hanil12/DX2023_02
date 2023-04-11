#pragma once
class MazeScene : public Scene
{
public:
	MazeScene();
	virtual ~MazeScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Maze> _maze;
};

