#include "framework.h"
#include "../Render/GlobalBuffer.h"

#include "Transform.h"

Transform::Transform()
{
	_matrixBuffer = make_shared<MatrixBuffer>();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	_scaleM = XMMatrixScaling(_scale.x, _scale.y, 1);
	_rotateM = XMMatrixRotationZ(_angle);
	_translateM = XMMatrixTranslation(_pos.x, _pos.y, 0.0f);

	_srt = _scaleM * _rotateM * _translateM;

	if (_parent.expired() == false)
	{
		_srt *= _parent.lock()->GetMatrix();
	}

	_matrixBuffer->SetData(_srt);
	_matrixBuffer->Update();
}

void Transform::SetBuffer(UINT slot)
{
	_matrixBuffer->SetVSBuffer(slot);
}

Vector2 Transform::GetWorldPosition()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, _srt);

	return Vector2(temp._41,temp._42);
}

Vector2 Transform::GetWorldScale()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, _scaleM);

	if (_parent.expired() == false)
	{
		Vector2 parentScale = _parent.lock()->GetWorldScale();

		return Vector2(temp._11 * parentScale.x, temp._22 * parentScale.y);
	}

	return Vector2(temp._11, temp._22);
}
