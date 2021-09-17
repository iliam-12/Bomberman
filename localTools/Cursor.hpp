/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Cursor.hpp
*/

#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include "Text.hpp"
#include <memory>

class Menu;
namespace lt {
    class Sound;
};

template <class T = Menu>
class Cursor {
public:
    // Note : coordinates are all normalized (between 0 and 1)
    Cursor(T &master, float x, float y, int alignment, const std::string &str,
        Texture2D &back, Texture2D &cursor, std::shared_ptr<lt::Sound> clic, void (T::*onClic)(float value));
    virtual ~Cursor() = default;
    Cursor(const Cursor &cpy) = delete;
    Cursor &operator=(const Cursor &src) = delete;

    void clicPressed(); // Call when left clic start being pressed
    void clicReleased(); // Call when left clic start being released
    void resized(); // Call when the window is resized
    void update(); // Update and draw button
    void setString(const std::string &str);
    void setPosition(float x, float y, int alignment = Text::CENTER);
    void setValue(float v);
private:
    T &master;
    void (Menu::*onClic)(float value);
    float x;
    float y;
    int minX, relMaxX;
    Texture2D &back;
    Texture2D &cursor;
    std::shared_ptr<lt::Sound> clic;
    bool pressed = false;
    bool hovered = false;
    Vector2 pos;
    Vector2 cpos;
    Rectangle bound;
    Rectangle src;
    Text txt;
    int align = Text::CENTER;
    const int width = 1920;
    const int height = 1080;
    float value = 0;
};

#include "Cursor.tpp"

#endif /* CURSOR_HPP_ */
