#include "framework.h"
#include "Camera.h"

Camera* Camera::_instance = nullptr;
Camera::Camera()
{
	_view = make_shared<Transform>();

	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);
	_projection->Update();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if(_target.expired() == false)
		FollowMode();

	_view->Update();
}

void Camera::PostRender()
{
	ImGui::SliderFloat2("Camera Pos", (float*)&_pos,0,1280);
	//ImGui::SliderFloat2("Camera Scale", (float*)&_scale,0,5);
	//ImGui::SliderFloat("Camera Angle", (float*)&_angle,0,2 * PI);

	//SetPosition(_pos);
	//SetScale(_scale);
	//SetAngle(_angle);
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
}

void Camera::SetViewPort(UINT width, UINT height)
{
}

void Camera::AddVector2(const Vector2& pos)
{
	_view->AddVector2(pos * -1.0f);
}

void Camera::SetPosition(const Vector2& pos)
{
	_view->SetPosition(pos * -1.0f);
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target.lock()->GetWorldPosition() - _offset;

	Vector2 lerp = LERP(_view->GetPos(), -targetPos, DELTA_TIME * 5.0f);
	_view->SetPosition(lerp);
}
