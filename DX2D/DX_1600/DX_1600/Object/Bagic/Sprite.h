#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector2 size);
	Sprite(wstring path, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	void Update();
	virtual void Render() override;

	void SetCurClip(Vector2 frame);
	void SetCurClip(Action::Clip clip);

	void SetLeft() { _actionBuffer->_data.isRight = 0; }
	void SetRight() { _actionBuffer->_data.isRight = 1; }

private:
	shared_ptr<ActionBuffer> _actionBuffer;

	shared_ptr<Vector2> _maxFrame;
};

