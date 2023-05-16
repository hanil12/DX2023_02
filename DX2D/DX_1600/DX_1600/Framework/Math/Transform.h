#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetBuffer(UINT slot);

	void SetScale(Vector2 scale) { _scale = scale; }
	void SetAngle(float angle) { _angle = angle; }
	void SetPosition(Vector2 pos) { _pos = pos; }

	const Vector2& GetScale() { return _scale; }
	const float& GetAngle() { return _angle; }
	const Vector2 GetPos() { return _pos; }

	const XMMATRIX& GetMatrix() { return _srt; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

private:
	shared_ptr<class MatrixBuffer> _matrixBuffer;

	Vector2 _scale = {1.0f, 1.0f};
	float _angle = 0.0f;
	Vector2 _pos = {0.0f,0.0f};

	XMMATRIX _scaleM = XMMatrixIdentity();
	XMMATRIX _rotateM = XMMatrixIdentity();
	XMMATRIX _translateM = XMMatrixIdentity();

	XMMATRIX _srt = XMMatrixIdentity();

	weak_ptr<Transform> _parent;
};

