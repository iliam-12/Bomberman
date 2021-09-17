/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Button2.hpp
*/

#ifndef BUTTON2_HPP_
#define BUTTON2_HPP_

#include "Text.hpp"
#include <memory>

class Menu;
namespace lt {
    class Sound;
};

template <class T = Menu>
class Button2 {
public:
    // Note : coordinates are all normalized (between 0 and 1)
    Button2(T &master, float x, float y, int alignment, const std::string &str,
        Texture2D &button, std::shared_ptr<lt::Sound> clic, void (T::*onClic)());
    virtual ~Button2() = default;
    Button2(const Button2 &cpy) = delete;
    Button2 &operator=(const Button2 &src) = delete;

    void clicPressed(); // Call when left clic start being pressed
    void clicReleased(); // Call when left clic start being released
    void resized(); // Call when the window is resized
    void update(); // Update and draw button
    void setString(const std::string &str);
    void setPosition(float x, float y, int alignment = Text::CENTER);
private:
    T &master;
    void (Menu::*onClic)();
    float x;
    float y;
    Texture2D &button;
    std::shared_ptr<lt::Sound> clic;
    bool pressed = false;
    bool hovered = false;
    Vector2 pos;
    Rectangle bound;
    Rectangle src;
    Text txt;
    int align = Text::CENTER;
    const int width = 1920;
    const int height = 1080;
};

#include "Button2.tpp"

#endif /* BUTTON2_HPP_ */
