#pragma once
class Planet
{
public:
	Planet(wstring file, Vector2 scale, float angle);
	~Planet();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPosition(pos); }
	void SetParent(shared_ptr<Transform> parent)
	{ _quad->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	shared_ptr<Transform> GetRevolution() {return _revolution; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _revolution;

	float _angle = 0.0f;
	float _revolutionAngle = 0.0f;
};

