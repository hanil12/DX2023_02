#pragma once
class CircleCollider
{
public:
	CircleCollider(float radius);
	~CircleCollider();

	void Update();
	void Render();

	void CreateData();
	void CreateVertices();

	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }

	bool IsCollision(shared_ptr<CircleCollider> other);

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

	// Rect와 공유하지 않는 함수
	void SetScale(float value) { _transform->SetScale({value, value}); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }

private:
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;

	float _radius;
};

