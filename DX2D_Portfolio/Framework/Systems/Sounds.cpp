#include "Framework.h"
#include "Sounds.h"

Sounds::Sounds()
	:count(150), volum(1.0f)
{
	System_Create(&system);

	system->init(count, FMOD_INIT_NORMAL, NULL);

	sound = new Sound * [count];
	channel = new Channel * [count];

	ZeroMemory(sound, sizeof(Sound*) * count);
	ZeroMemory(channel, sizeof(Channel*) * count);
}

Sounds::~Sounds()
{
	if (channel != NULL) { // 150개중 1개만 있어도 널은 아님
		for (int i = 0; i < count; i++) {
			if (channel[i])channel[i]->stop(); // 일단 사운드 있는걸 멈춰 놓고
		}
	}

	if (sound != NULL) {
		for (int i = 0; i < count; i++) {
			if (sound[i])sound[i]->release(); 
		}
	}

	SAFE_DELETE_ARRAY(channel);
	SAFE_DELETE_ARRAY(sound);

	if (system != NULL) {
		system->release();
		system->close();
	}

	sounds.clear();
}

void Sounds::Update()
{
	system->update();
}

void Sounds::AddSound(string name, wstring file, bool loop)
{
	if (loop == true) {
		system->createStream(String::ToString(file).c_str(), FMOD_LOOP_NORMAL,
			NULL, &sound[sounds.size()]);
	}

	else {
		system->createStream(String::ToString(file).c_str(), FMOD_DEFAULT,
			NULL, &sound[sounds.size()]);
	}

	sounds[name] = &sound[sounds.size()];
}

void Sounds::Play(string name, float volum)
{
	int count = 0;
	iter = sounds.begin();
	
	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			system->playSound(*iter->second, NULL, false, &channel[count]);
			channel[count]->setVolume(volum);
		}
	}
}

void Sounds::Stop(string name)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->stop();
			break;
		}
	}
}

void Sounds::Pause(string name)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->setPaused(true);
			break;
		}
	}
}

void Sounds::Resum(string name)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool Sounds::isPlaying(string name)
{
	bool play = false;
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->isPlaying(&play);
			break;
		}
	}
	return play;
}

bool Sounds::isPause(string name)
{
	bool pause = false;
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->getPaused(&pause);
			break;
		}
	}
	return pause;
}

void Sounds::SetVolum(string name, float volum)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->setVolume(volum);
			break;
		}
	}
}

float Sounds::GetVolum(string name)
{
	float volum = 0.0f;
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); iter++, count++) {
		if (name == iter->first) {
			channel[count]->getVolume(&volum);
			break;
		}
	}
	return volum;
}