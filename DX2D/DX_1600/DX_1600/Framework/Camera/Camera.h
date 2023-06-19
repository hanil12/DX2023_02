#pragma once
class Camera
{
private:
	Camera();
	~Camera();

public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new Camera();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if(_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void PostRender();

	void ShakeStart(float magnitude, float duration, float reduceDamping = 1.0f);

	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetCameraBuffer() { _view->SetBuffer(1); }
	void SetProjectionBuffer() { _projection->SetVSBuffer(2); }

	void AddAngle(float angle) { _view->AddAngle(-angle); }
	void AddScale(const Vector2& scale) { _view->AddScale(scale); }
	void AddVector2(const Vector2& pos);

	void SetAngle(float angle) { _view->SetAngle(-angle); }
	void SetScale(const Vector2& scale) { _view->SetScale(scale); }
	void SetPosition(const Vector2& pos);

	void SetTarget(shared_ptr<Transform> target) { _target = target; }

private:
	void FollowMode();

	static Camera* _instance;

	shared_ptr<Transform>		 _view;
	shared_ptr<MatrixBuffer>	 _projection;

	weak_ptr<Transform> _target;
	Vector2 _offset;

	Vector2 _pos;
	Vector2 _scale = {1,1};
	float	_angle = 0;
};
