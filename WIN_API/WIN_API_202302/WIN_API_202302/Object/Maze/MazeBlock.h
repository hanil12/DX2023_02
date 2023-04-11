#pragma once
class MazeBlock
{
public:
	enum class BlockType
	{
		NONE,
		ABLE,
		DISABLE,
	};

	MazeBlock();
	~MazeBlock();

	void Update();
	void Render(HDC hdc);

	void SetType(BlockType type) { _type = type;}
	void SetPosition(Vector2 pos) { _rect->SetCenter(pos); }

private:
	vector<HBRUSH> _brushes;
	BlockType _type = BlockType::NONE;
	shared_ptr<Collider> _rect;
};

