/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <string>
#include <raylib.h>

class Text {
public:
    enum Align {
        LEFT = 0x1,
        RIGHT = 0x2,
        UP = 0x4,
        DOWN = 0x8,
        CENTER = LEFT | RIGHT | UP | DOWN
    };
    Text(int fontSize = 24, int spacing = 2);
    virtual ~Text();
    Text(const Text &cpy) = delete;
    Text &operator=(const Text &src) = delete;

    void setString(const std::string &str);
    void setPosition(float x, float y, int alignment = CENTER);
    void setColor(Color color);
    void draw();
    void resized();
    static void loadFont(const std::string &filename);
    static void unloadFont();
private:
    static Font font;
    std::string str;
    float x, y;
    Vector2 pos;
    int align;
    Color color = WHITE;
    const int fontSize;
    const int spacing;
    const int width = 1920;
    const int height = 1080;
};

#endif /* TEXT_HPP_ */
