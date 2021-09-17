/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Bonus.cpp
*/
#include "Bonus.hpp"
#include "Save.hpp"
#include "DataPack.hpp"

Bonus::Bonus(Game *master, std::shared_ptr<GraphicMgr> &mgr, enum Type type) :
    Entity(master, mgr, TypeID::BONUS), type(type)
{}

Bonus::Bonus(Game *master, const BonusData &data) :
    Entity(master, data.base), type(data.type)
{}

Bonus::~Bonus()
{}

unsigned char Bonus::collect()
{
    alive = false;
    return (type);
}

void Bonus::save(Save &game) const
{
    DataPack<BonusData>(game["Bonus"]).push({Entity::save(), type});
}

void Bonus::loadAll(Game *master, Save &game)
{
    BonusData tmp;
    DataPack<BonusData> datas(game["Bonus"]);

    while (datas.pop(tmp)) {
        Entity::load<Bonus>(master, tmp);
    }
}
