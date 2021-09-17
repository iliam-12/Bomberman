/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Bomb.cpp
*/
#include "Bomb.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Save.hpp"
#include "DataPack.hpp"

Bomb::Bomb(Game *master, std::shared_ptr<GraphicMgr> &mgr, Player *owner, int *bombs, int power) :
    Entity(master, mgr, TypeID::BOMB), owner(owner), bombs(bombs), power(power)
{
    --(*bombs);
}

Bomb::Bomb(Game *master, const BombData &data) :
    Entity(master, data.base), owner(master->getPlayer(data.link)), lifetime(data.lifetime), bombs(owner->getBombLink()), power(data.power)
{
}

Bomb::~Bomb()
{
    ++(*bombs);
}

bool Bomb::onUpdate()
{
    if (--lifetime)
        return (true);
    master->makeExplosion(owner, x, y, power);
    return (false);
}

void Bomb::save(Save &game) const
{
    DataPack<BombData>(game["Bomb"]).push({Entity::save(), owner->getLink(), lifetime, power});
}

void Bomb::loadAll(Game *master, Save &game)
{
    BombData tmp;
    DataPack<BombData> datas(game["Bomb"]);

    while (datas.pop(tmp)) {
        Entity::load<Bomb>(master, tmp);
    }
}
