#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	virtual ~SpriteScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	Vector2 _curFrame;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;
};

