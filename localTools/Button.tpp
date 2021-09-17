/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Button.tpp
*/
#include "Button.hpp"

template <class T>
Button<T>::Button(T &master, float x, float y, Texture2D &button, std::shared_ptr<lt::Sound> clic, void (T::*onClic)()) :
    master(master), onClic(onClic), x(x), y(y), button(button), clic(clic), src({0.f, 0.f, (float) button.width, button.height / 3.f})
{
    bound.width = src.width;
    bound.height = src.height;
    resized();
}

template <class T>
Button<T>::~Button()
{}

template <class T>
void Button<T>::clicPressed()
{
    if (hovered) {
        pressed = true;
        src.y = 2 * src.height;
    }
}

template <class T>
void Button<T>::clicReleased()
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
void Button<T>::resized()
{
    switch (align & 0x3) {
        case LEFT:
            pos.x = x * width;
            break;
        case RIGHT:
            pos.x = x * width - bound.width;
            break;
        default:
            pos.x = x * width - bound.width / 2;
    }
    switch (align & 0x12) {
        case UP:
            pos.y = y * height;
            break;
        case DOWN:
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
}

template <class T>
void Button<T>::update()
{
    if (CheckCollisionPointRec(GetMousePosition(), bound)) {
        if (!hovered) {
            hovered = true;
            src.y = (pressed) ? src.height * 2 : src.height;
        }
    } else {
        if (hovered) {
            hovered = false;
            src.y = 0;
        }
    }
    DrawTextureRec(button, src, pos, WHITE);
}

template <class T>
void Button<T>::setPosition(float _x, float _y, Align alignment)
{
    x = _x;
    y = _y;
    align = alignment;
    resized();
}
