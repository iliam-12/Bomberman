/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Button2.tpp
*/
#include "Button2.hpp"
#include "Text.hpp"
#include "Sound.hpp"

template <class T>
Button2<T>::Button2(T &master, float x, float y, int alignment, const std::string &str,
    Texture2D &button, std::shared_ptr<lt::Sound> clic, void (T::*onClic)()) :
    master(master), onClic(onClic), x(x), y(y), button(button), clic(clic), src({0.f, 0.f, (float) button.width, button.height / 3.f}), align(alignment)
{
    bound.width = button.width;
    bound.height = button.height / 3;
    txt.setString(str);
    resized();
}

template <class T>
void Button2<T>::clicPressed()
{
    if (hovered) {
        pressed = true;
        src.y = 2 * src.height;
    }
}

template <class T>
void Button2<T>::clicReleased()
{
    if (!pressed)
        return;
    pressed = false;
    if (hovered) {
        clic->start();
        src.y = src.height;
        (master.*onClic)();
    }
}

template <class T>
void Button2<T>::resized()
{
    switch (align & 0x3) {
        case Text::LEFT:
            pos.x = x * width;
            break;
        case Text::RIGHT:
            pos.x = x * width - bound.width;
            break;
        default:
            pos.x = x * width - bound.width / 2;
    }
    switch (align & 0x12) {
        case Text::UP:
            pos.y = y * height;
            break;
        case Text::DOWN:
            pos.y = y * height - bound.height;
            break;
        default:
            pos.y = y * height - bound.height / 2;
    }
    if (pos.x + bound.width > width)
        pos.x = width - bound.width;
    if (pos.x < 0)
        pos.x = 0;
    if (pos.y + bound.height > height)
        pos.y = height - bound.height;
    if (pos.y < 0)
        pos.y = 0;
    bound.x = pos.x;
    bound.y = pos.y;
    float centerX = (bound.x + bound.width / 2) / (float) width;
    float centerY = (bound.y + bound.height / 2) / (float) height;
    txt.setPosition(centerX, centerY);
}

template <class T>
void Button2<T>::update()
{
    if (CheckCollisionPointRec(GetMousePosition(), bound)) {
        if (!hovered) {
            hovered = true;
            if (pressed) {
                src.y =  src.height * 2;
                txt.setColor(BLACK);
            } else {
                src.y = src.height;
                txt.setColor(YELLOW);
            }
        }
    } else {
        if (hovered) {
            hovered = false;
            src.y = 0;
            txt.setColor(WHITE);
        }
    }
    DrawTextureRec(button, src, pos, WHITE);
    txt.draw();
}

template <class T>
void Button2<T>::setString(const std::string &str)
{
    txt.setString(str);
}

template <class T>
void Button2<T>::setPosition(float _x, float _y, int alignment)
{
    x = _x;
    y = _y;
    align = alignment;
    resized();
}
