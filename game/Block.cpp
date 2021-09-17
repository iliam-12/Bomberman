/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Block.cpp
*/
#include "Block.hpp"
#include "Game.hpp"
#include "Save.hpp"
#include "DataPack.hpp"

Block::Block(Game *master, std::shared_ptr<GraphicMgr> &mgr) :
    Entity(master, mgr, TypeID::BREAKABLE_BLOCK)
{}

Block::Block(Game *master, const BlockData &data) :
    Entity(master, data.base), destroyed(data.destroyed)
{}

Block::~Block()
{}

void Block::destroy()
{
    destroyed = 10;
    immobilize();
    master->maybePutBonus(x, y);
}

bool Block::onUpdate()
{
    if (destroyed) {
        // Animated breaking sequence
        return (--destroyed);
    }
    return (true);
}

void Block::save(Save &game) const
{
    DataPack<BlockData>(game["Block"]).push({Entity::save(), destroyed});
}

void Block::loadAll(Game *master, Save &game)
{
    BlockData tmp;
    DataPack<BlockData> datas(game["Block"]);

    while (datas.pop(tmp)) {
        Entity::load<Block>(master, tmp);
    }
}
