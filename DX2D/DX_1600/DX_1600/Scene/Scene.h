#pragma once
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() {};
	virtual void End() {};

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PreRender() {}
	virtual void PostRender() {}

private:
};

