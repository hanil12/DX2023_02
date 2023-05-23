#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
	// 오른쪽 1만큼 이동
	// A : 1초에 300번 업데이트 -> 300 * (1/300) = 1
	// B : 1초에 100번 업데이트 -> 100 * (1/100) = 1

	// 1초에 몇번 진동하는지
	QueryPerformanceFrequency((LARGE_INTEGER*) &_periodFrequency);
	
	// 프로그램이 시작할 때 지금까지 CPU의 진동수
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
