#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	_blocks.reserve(_poolCountY);
	Vector2 offset = {400,150};
	for (int y = 0; y < _poolCountY; y++)
	{
		vector<shared_ptr<MazeBlock>> blocksX;
		blocksX.reserve(_poolCountX);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<MazeBlock> block = make_shared<MazeBlock>();
			block->SetType(MazeBlock::BlockType::DISABLE);
			Vector2 distance = {17 * x,17 * y};
			block->SetPosition(offset + distance);
			blocksX.push_back(block);
		}
		_blocks.push_back(blocksX);
	}

	CreateMaze();

	_blocks[1][1]->SetType(MazeBlock::BlockType::START);
	_blocks[_poolCountY - 2][_poolCountX - 2]->SetType(MazeBlock::BlockType::END);
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blocksX : _blocks)
	{
		for (auto block : blocksX)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blocksX : _blocks)
	{
		for (auto block : blocksX)
		{
			block->Render(hdc);
		}
	}
}

// Maze for Programmers
void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
			else
				_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	// �����ϰ� ������ Ȥ�� �Ʒ������� ���� �մ� �۾�
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			// ó�� ������ ��尡 �ƴ� ���
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// ������������ ������ Ȥ�� �Ʒ��� �� �ձ� ����
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				continue;
			}

			// �������� ���� Ȥ�� �Ʒ��θ� �վ��� �� ���� �Ȼ���� �� ����ó��
			if (y == _poolCountY - 2)
			{
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			if (x == _poolCountX - 2)
			{
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// �����ϰ� ������ Ȥ�� �Ʒ��� �� �ձ�
			const int randValue = rand() % 2;
			if(randValue == 0) // ������ ��ձ�
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else // �Ʒ��� ��ձ�
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}
}

MazeBlock::BlockType Maze::GetBlockType(int y, int x)
{
	if(y < 0 || y > _poolCountY)
		return MazeBlock::BlockType::NONE;
	if(x < 0 || x > _poolCountX)
		return MazeBlock::BlockType::NONE;

	return _blocks[y][x]->GetType();
}
