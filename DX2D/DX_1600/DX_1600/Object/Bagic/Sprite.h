#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector2 size);
	Sprite(wstring path, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	void Update();
	virtual void Render() override;

	void SetCurFrame(Vector2 frame);
	void SetCurFrame(Action::Clip clip);

private:
	shared_ptr<ActionBuffer> _actionBuffer;

	shared_ptr<Vector2> _maxFrame;
};

