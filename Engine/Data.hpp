/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Data.hpp
*/

#ifndef DATA_HPP_
#define DATA_HPP_

struct GraphicData {
    int mesh;
    int material;
    float x;
    float y;
    float z;
    float c;
    float s;
    unsigned short id;
    bool grabbed;
};

struct EntityData {
    GraphicData graphic;
    int x;
    int y;
    float mov[4];
    int duration;
    bool alive;
    unsigned char typeID;
};

struct BlockData {
    EntityData base;
    int destroyed;
};

struct BombData {
    EntityData base;
    int link;
    int lifetime;
    int power;
};

struct BonusData {
    EntityData base;
    unsigned char type;
};

struct PlayerData {
    EntityData base;
    int killed;
    int gamepad;
    int duration;
    int bombs;
    int bombPower;
    int score;
    bool bypassing;
    bool collided;
};

enum TypeID : unsigned char {
    SOLID_BLOCK,
    BOMB,
    BREAKABLE_BLOCK,
    PLAYER,
    EXPLOSION,
    BONUS
};

#endif /* DATA_HPP_ */
