/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Music.hpp
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include <raylib.h>

namespace lt {
class Music {
public:
    Music(const std::string &filename, bool loopy = true);
    virtual ~Music();
    Music(const Music &cpy) = delete;
    Music &operator=(const Music &src) = delete;

    void start(); // Start music from beginning
    void pause(); // Pause music
    void unpause(); // Resume music
    void update(); // Update music
    void stop(); // Stop music
    void setVolume(float volume); // 0 for 0% and 1 for 100%
private:
    ::Music music;
    const bool loopy;
    bool reloop = false;
};
};

#endif /* MUSIC_HPP_ */
