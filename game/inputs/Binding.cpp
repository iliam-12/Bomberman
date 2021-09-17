/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Binding.cpp
*/
#include "Binding.hpp"
#include <raylib.h>
#include <cmath>

Binding::Binding(int gamepad) : gamepad(gamepad)
{}

Binding::~Binding()
{}

void Binding::enable(bool state)
{
    enabled = state;
}

bool Binding::isConnected() const
{
    if (gamepad == -1)
        return (true);
    return (IsGamepadAvailable(gamepad));
}

bool Binding::putBomb()
{
    if (gamepad == -1) {
        return (IsKeyDown(KEY_SPACE));
    } else {
        return (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN));
    }
}

Movement Binding::getMove()
{
    if (gamepad == -1) {
        if (IsKeyPressed(KEY_LEFT))
            last = Movement::LEFT;
        if (IsKeyPressed(KEY_RIGHT))
            last = Movement::RIGHT;
        if (IsKeyPressed(KEY_UP))
            last = Movement::UP;
        if (IsKeyPressed(KEY_DOWN))
            last = Movement::DOWN;
        switch (last) {
            case Movement::LEFT:
                if (IsKeyDown(KEY_LEFT))
                    return (Movement::LEFT);
                last = Movement::IDLE;
                break;
            case Movement::RIGHT:
                if (IsKeyDown(KEY_RIGHT))
                    return (Movement::RIGHT);
                last = Movement::IDLE;
                break;
            case Movement::UP:
                if (IsKeyDown(KEY_UP))
                    return (Movement::UP);
                last = Movement::IDLE;
                break;
            case Movement::DOWN:
                if (IsKeyDown(KEY_DOWN))
                    return (Movement::DOWN);
                last = Movement::IDLE;
                break;
            case Movement::IDLE:;
        }
        if (last == Movement::IDLE) {
            if (IsKeyDown(KEY_DOWN))
                last = Movement::DOWN;
            else if (IsKeyDown(KEY_UP))
                last = Movement::UP;
            else if (IsKeyDown(KEY_RIGHT))
                last = Movement::RIGHT;
            else if (IsKeyDown(KEY_LEFT))
                last = Movement::LEFT;
        }
        return (last);
    } else {
        const float x = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
        const float y = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
        if (fabs(x) + fabs(y) < 0.2)
            return (Movement::IDLE);
        if (fabs(x) > fabs(y)) {
            return (x > 0 ? Movement::RIGHT : Movement::LEFT);
        } else {
            return (y > 0 ? Movement::DOWN : Movement::UP);
        }
    }
}
