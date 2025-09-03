#include "pch.h"
#include "BGMMusicScript.h"

BGMMusicScript::~BGMMusicScript()
{
    musicList.clear();
}

void BGMMusicScript::PlayBGMMusic(int key)
{
    if (!music.openFromFile(musicList[key]))
    {
        Debug::Log("Error loading music");
        return;
    }

    music.setLooping(true);
    music.setVolume(10);
    music.play();
}

void BGMMusicScript::PauseBGMMusic(bool a)
{
    if (!a) {
        music.play();
    }
    else {
        music.pause();
    }
}

void BGMMusicScript::StopBGMMusic()
{
    music.stop();
}
