/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Music.cpp
*/
#include "Music.hpp"

// in main, use IsAudioStreamPlaying(AudioStream stream); to loop music

lt::Music::Music(const std::string &filename, bool loopy) : loopy(loopy)
{
    this->music = LoadMusicStream(filename.c_str());
}

lt::Music::~Music()
{
    UnloadMusicStream(this->music);
}

void lt::Music::start()
{
    PlayMusicStream(this->music);
    reloop = loopy;
}

void lt::Music::pause()
{
    PauseMusicStream(this->music);
    reloop = false;
}

void lt::Music::unpause()
{
    ResumeMusicStream(this->music);
    reloop = loopy;
}

void lt::Music::stop()
{
    StopMusicStream(this->music);
    reloop = false;
}

void lt::Music::update()
{
    UpdateMusicStream(music);
    if (reloop && !IsMusicStreamPlaying(this->music))
        PlayMusicStream(this->music);
}

void lt::Music::setVolume(float volume)
{
    SetMusicVolume(this->music, volume);
}
