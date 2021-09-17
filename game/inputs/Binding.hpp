/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Binding.hpp
*/

#ifndef BINDING_HPP_
#define BINDING_HPP_

#include <iostream>
#include <string>
#include <memory>

enum class Movement : unsigned char {
    IDLE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Binding {
public:
    Binding(int gamepad = -1);
    virtual ~Binding();
    Binding(const Binding &cpy) = delete;
    Binding &operator=(const Binding &src) = delete;

    bool isConnected() const;
    int getGamepad() const {
        return gamepad;
    }
    void enable(bool state);
    Movement getMove();
    bool putBomb();
private:
    int gamepad;
    bool enabled = true;
    Movement last = Movement::IDLE;
};

#endif /* BINDING_HPP_ */
