/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>
#include <memory>
#include <raylib.h>
#include "Sound.hpp"

class Menu;

template <class T = Menu>
class Button {
public:
    enum Align {
        LEFT = 0x1,
        RIGHT = 0x2,
        UP = 0x4,
        DOWN = 0x8,
        CENTER = LEFT | RIGHT | UP | DOWN
    };
    // Note : coordinates are all normalized (between 0 and 1)
    Button(T &master, float x, float y, Texture2D &button, std::shared_ptr<lt::Sound> clic, void (T::*onClic)());
    virtual ~Button();
    Button(const Button &cpy) = delete;
    Button &operator=(const Button &src) = delete;

    void clicPressed(); // Call when left clic start being pressed
    void clicReleased(); // Call when left clic start being released
    void resized(); // Call when the window is resized
    void update(); // Update and draw button
    void setPosition(float x, float y, Align alignment = CENTER);
private:
    T &master;
    void (T::*onClic)();
    float x;
    float y;
    Texture2D &button;
    std::shared_ptr<lt::Sound> clic;
    bool pressed = false;
    bool hovered = false;
    Align align = CENTER;
    Vector2 pos;
    Rectangle bound;
    Rectangle src;
    const int width = 1920;
    const int height = 1080;
};

#include "Button.tpp"

#endif /* BUTTON_HPP_ */
