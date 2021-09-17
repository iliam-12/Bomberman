/*
** EPITECH PROJECT, 2021
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** ScoreBoard
*/

#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard(int i)
{
    i++;
    skin_kevin = LoadTexture("resources/texture/skin_kevin.png");
    skin_alex = LoadTexture("resources/texture/skin_alex.png");
    skin_fox = LoadTexture("resources/texture/skin_fox.png");
    skin_black = LoadTexture("resources/texture/skin_noir.png");
    bomb_up = LoadTexture("resources/texture/bomb_up_icon.png");
    fire = LoadTexture("resources/texture/fire_icon.png");
    speed = LoadTexture("resources/texture/speed_icon.png");
    background = LoadTexture("resources/texture/background.png");
    fontm = LoadFont("resources/font/minecraft_font.ttf");

}

ScoreBoard::~ScoreBoard()
{
    // UnloadTexture(skin_kevin);
    // UnloadTexture(skin_alex);
    // UnloadTexture(skin_fox);
    // UnloadTexture(skin_black);
    // UnloadTexture(bomb_up);
    // UnloadTexture(fire);
    // UnloadTexture(speed);
    // UnloadTexture(background);
}

void ScoreBoard::print_background(float x, float y)
{
    DrawTexture(background, x, y, WHITE);
}

void ScoreBoard::print_skin_kevin(float x, float y)
{
    DrawTexture(skin_kevin, x, y, WHITE);
}

void ScoreBoard::print_skin_alex(float x, float y)
{
    DrawTexture(skin_alex, x, y, WHITE);
}

void ScoreBoard::print_skin_fox(float x, float y)
{
    DrawTexture(skin_fox, x, y, WHITE);
}

void ScoreBoard::print_skin_black(float x, float y)
{
    DrawTexture(skin_black, x, y, WHITE);
}

void ScoreBoard::print_bomb_up(float x, float y)
{
    DrawTexture(bomb_up, x, y, WHITE);
}

void ScoreBoard::print_fire(float x, float y)
{
    DrawTexture(fire, x, y, WHITE);
}

void ScoreBoard::print_speed(float x, float y)
{
    DrawTexture(speed, x, y, WHITE);
}

Font ScoreBoard::ret_font()
{
    return (fontm);
}