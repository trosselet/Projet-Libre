#pragma once
#include "scripts/Script.h"
#include "KeyCounter.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Text.hpp>

#include <map>

class RigidBody2D;

class BGMMusicScript : public IScript
{
public:
	~BGMMusicScript() override;
	void AddMusic(int key, const char* musicFile) { musicList.emplace(key, musicFile); }
	
	void PlayBGMMusic(int key);
	void PauseBGMMusic(bool a);
	void StopBGMMusic();
	void SetVolume(int volume) { music.setVolume(volume); }

private:
	std::map<int, const char*> musicList;
	sf::Music music;
};