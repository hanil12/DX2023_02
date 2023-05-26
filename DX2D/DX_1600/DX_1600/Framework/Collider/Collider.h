#pragma once
class Collider
{
protected:
	enum class ColType
	{
		NONE,
		CIRCLE,
		RECT
	};

public:
	Collider(ColType type);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();

	void CreateData();
	virtual void CreateVertices() abstract;

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;

	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }



protected:
	ColType _type;

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;
};

