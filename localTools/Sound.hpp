/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Sound.hpp
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <string>
#include <raylib.h>

namespace lt {
class Sound {
public:
    Sound(const std::string &filename, int minChannels);
    virtual ~Sound();
    Sound(const Sound &cpy) = delete;
    Sound &operator=(const Sound &src) = delete;

    void start();
    void pauseAll();
    void unpauseAll();
    void stopAll();
    static void setGlobalVolume(float volume); // Set volume for every subsequent sounds, 0 for 0% and 1 for 100%
    static void setPath(const std::string &str);
    void setLocalVolume(float volume); // Set volume, 0 for 0% and 1 for 100% (to multiply with global volume)
private:
    static std::string path;
    ::Sound sound;
    bool loaded = true;
};
};

#endif /* SOUND_HPP_ */
