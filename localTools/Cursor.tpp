/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Cursor.tpp
*/
#include "Cursor.hpp"
#include "Text.hpp"
#include "Sound.hpp"

template <class T>
Cursor<T>::Cursor(T &master, float x, float y, int alignment, const std::string &str,
    Texture2D &back, Texture2D &cursor, std::shared_ptr<lt::Sound> clic, void (T::*onClic)(float value)) :
    master(master), onClic(onClic), x(x), y(y), back(back), cursor(cursor), clic(clic), src({0.f, 0.f, (float) cursor.width, cursor.height / 3.f}), align(alignment)
{
    bound.width = back.width;
    bound.height = back.height;
    txt.setString(str);
    resized();
}

template <class T>
void Cursor<T>::clicPressed()
{
    if (hovered) {
        pressed = true;
        src.y = 2 * src.height;
    }
}

template <class T>
void Cursor<T>::clicReleased()
{
    if (!pressed)
        return;
    pressed = false;
    clic->start();
    src.y = (hovered) ? src.height : 0;
    (master.*onClic)(value);
}

template <class T>
void Cursor<T>::resized()
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
    cpos.y = bound.y + bound.height / 2 - src.height / 2;
    minX = bound.x;
    relMaxX = bound.width - cursor.width;
    setValue(value);
}

template <class T>
void Cursor<T>::update()
{
    DrawTextureV(back, pos, WHITE);
    if (pressed) {
        setValue((GetMousePosition().x - pos.x - src.width / 2) / (float) relMaxX);
    } else {
        if (CheckCollisionPointRec(GetMousePosition(), bound)) {
            if (!hovered) {
                hovered = true;
                src.y = src.height;
                txt.setColor(YELLOW);
            }
        } else {
            if (hovered) {
                hovered = false;
                src.y = 0;
                txt.setColor(WHITE);
            }
        }
    }
    DrawTextureRec(cursor, src, cpos, WHITE);
    txt.draw();
}

template <class T>
void Cursor<T>::setString(const std::string &str)
{
    txt.setString(str);
}

template <class T>
void Cursor<T>::setPosition(float _x, float _y, int alignment)
{
    x = _x;
    y = _y;
    align = alignment;
    resized();
}

template <class T>
void Cursor<T>::setValue(float v)
{
    if (v < 0)
        v = 0;
    else if (v > 1)
        v = 1;
    value = v;
    cpos.x = minX + relMaxX * v;
}
