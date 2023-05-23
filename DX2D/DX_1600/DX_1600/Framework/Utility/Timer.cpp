#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
	// ������ 1��ŭ �̵�
	// A : 1�ʿ� 300�� ������Ʈ -> 300 * (1/300) = 1
	// B : 1�ʿ� 100�� ������Ʈ -> 100 * (1/100) = 1

	// 1�ʿ� ��� �����ϴ���
	QueryPerformanceFrequency((LARGE_INTEGER*) &_periodFrequency);
	
	// ���α׷��� ������ �� ���ݱ��� CPU�� ������
	QueryPerformanceCounter((LARGE_INTEGER*) &_lastTime);

	_timeSacle = 1.0 / (double)_periodFrequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*) &_curTime);
	_deltaTime = (double)(_curTime - _lastTime) * _timeSacle;

	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_deltaTime = (double)(_curTime - _lastTime) * _timeSacle;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	if (_oneSecCount >= 1)
	{
		_frameRate = _frameCount;
		// FPS : frame per second
		_oneSecCount = 0;
		_frameCount = 0;
	}

	_runTime += _deltaTime;
}
