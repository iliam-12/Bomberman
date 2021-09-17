/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Sound.cpp
*/
#include "Sound.hpp"

std::string lt::Sound::path = "resources/audio/";

lt::Sound::Sound(const std::string &filename, int minChannels)
{
    this->sound = LoadSound((path + filename).c_str());
    if (filename.empty())
        loaded = false;
}

lt::Sound::~Sound()
{
    StopSound(sound);
    UnloadSound(sound);
}

void lt::Sound::start()
{
    if (loaded) {
        PlaySoundMulti(this->sound);
    }
}

void lt::Sound::pauseAll()
{
    PauseSound(this->sound);
}

void lt::Sound::unpauseAll()
{
    ResumeSound(this->sound);
}

void lt::Sound::stopAll()
{
    StopSoundMulti();
}

void lt::Sound::setGlobalVolume(float volume)
{
    SetMasterVolume(volume); // 1.00 is max
}

void lt::Sound::setLocalVolume(float volume)
{
    SetSoundVolume(this->sound, volume); // 1.00 is max
}

void lt::Sound::setPath(const std::string &_path)
{
    path = _path;
}
