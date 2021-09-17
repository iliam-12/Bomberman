/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Text.cpp
*/
#include "Text.hpp"

Font Text::font;

Text::Text(int fontSize, int spacing) : fontSize(fontSize), spacing(spacing)
{}

Text::~Text()
{}

void Text::setString(const std::string &_str)
{
    if (str == _str)
        return;
    str = _str;
    resized();
}

void Text::setPosition(float _x, float _y, int alignment)
{
    align = alignment;
    x = _x;
    y = _y;
    resized();
}

void Text::resized()
{
    Vector2 size = MeasureTextEx(font, str.c_str(), fontSize, spacing);

    switch (align & 0x3) {
        case LEFT:
            pos.x = x * width;
            break;
        case RIGHT:
            pos.x = x * width - size.x;
            break;
        default:
            pos.x = x * width - size.x / 2;
    }
    switch (align & 0x12) {
        case UP:
            pos.y = y * height;
            break;
        case DOWN:
            pos.y = y * height - size.y;
            break;
        default:
            pos.y = y * height - size.y / 2;
    }
    if (pos.x + size.x > width)
        pos.x = width - size.x;
    if (pos.x < 0)
        pos.x = 0;
    if (pos.y + size.y > height)
        pos.y = height - size.y;
    if (pos.y < 0)
        pos.y = 0;
}

void Text::loadFont(const std::string &filename)
{
    if (filename.empty()) {
        font = GetFontDefault();
        return;
    }
    font = LoadFont(filename.c_str());
}

void Text::unloadFont()
{
    UnloadFont(font);
}

void Text::setColor(Color c)
{
    color = c;
}

void Text::draw()
{
    DrawTextEx(font, str.c_str(), pos, fontSize, spacing, color);
}
