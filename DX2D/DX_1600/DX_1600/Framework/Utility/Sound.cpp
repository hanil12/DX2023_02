#include "framework.h"
#include "Sound.h"

Sound* Sound::_instance = nullptr;
Sound::Sound()
{
	FMOD::System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

Sound::~Sound()
{
}

void Sound::Update()
{
	_soundSystem->update();
}

void Sound::Add(string key, string file, bool bgm)
{
	if(_soundMap.count(key) > 0)
		return;

	SoundInfo info;

	if(bgm)
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, &info._sound);
	else
		_soundSystem->createStream(file.c_str(), FMOD_DEFAULT, nullptr, &info._sound);

	// 표현식이 false를 반환하면 오류를 터트림
	assert(info._sound != nullptr);

	_soundMap[key] = info;
}

void Sound::Play(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundSystem->playSound(_soundMap[key]._sound, nullptr, false, &_soundMap[key]._channel);
	_soundMap[key]._channel->setVolume(volume);
}

void Sound::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if(_soundMap[key]._channel == nullptr)
		return;

	_soundMap[key]._channel->stop();
}

void Sound::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]._channel == nullptr)
		return;

	_soundMap[key]._channel->setPaused(true);
}

void Sound::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]._channel == nullptr)
		return;

	_soundMap[key]._channel->setPaused(false);
}

void Sound::SetVolume(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]._channel == nullptr)
		return;

	if(volume < 0.0f)
		volume = 0.0f;

	if(volume > 2.0f)
		volume = 2.0f;

	_soundMap[key]._channel->setVolume(volume);
}

bool Sound::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;

	if (_soundMap[key]._channel == nullptr)
		return false;

	bool isPlay = false;
	_soundMap[key]._channel->isPlaying(IN &isPlay);

	return isPlay;
}
