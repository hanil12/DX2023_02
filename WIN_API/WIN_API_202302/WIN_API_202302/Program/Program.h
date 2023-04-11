#pragma once
class Program
{
public:
	Program();
	~Program();

	// 게임은 Update와 Render가 두부분으로 갈린다.
	void Update();
	void Render(HDC hdc);

	// 백버퍼
	static HDC _backBuffer;

private:
	shared_ptr<Scene> _curScene;

	HBITMAP _hBit;
};

