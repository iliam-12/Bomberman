/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Explosion.cpp
*/
#include "Explosion.hpp"
#include "Engine/GraphicObject.hpp"
#include "DataPack.hpp"
#include "Save.hpp"

Explosion::Explosion(Game *master, std::shared_ptr<GraphicMgr> &mgr, bool xAxis) :
    Entity(master, mgr, TypeID::EXPLOSION)
{
    if (xAxis)
        graphic->setRotation(3.1415926 / 2);
}

Explosion::Explosion(Game *master, const EntityData &data) :
    Entity(master, data)
{
}

Explosion::~Explosion()
{}

bool Explosion::onUpdate()
{
    if (!lifetime)
        return (false);
    lifetime--;
    return (true);
}

void Explosion::save(Save &game) const
{
    DataPack<EntityData>(game["Explosion"]).push(Entity::save());
}

void Explosion::loadAll(Game *master, Save &game)
{
    EntityData tmp;
    DataPack<EntityData> datas(game["Explosion"]);

    while (datas.pop(tmp)) {
        Entity::load<Explosion>(master, tmp);
    }
}
