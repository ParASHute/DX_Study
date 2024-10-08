#pragma once

using namespace FMOD;

class Sounds : public SingletonBase<Sounds> {
public:
	friend SingletonBase<Sounds>;

	void Update();
	
	void AddSound(string name, wstring file, bool loop = false);

	void Play(string name, float volum = 1.0f);
	void Stop(string name);
	void Pause(string name);
	void Resum(string name);

	bool isPlaying(string name);
	bool isPause(string name);

	void SetVolum(string name, float volum);
	float GetVolum(string name);

private:
	Sounds();
	~Sounds();

private:
	System* system;
	Sound** sound;
	Channel** channel;

	UINT count;

	map<string, Sound**> sounds;
	map<string, Sound**>::iterator iter;

	float volum;
};