/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Entity.cpp
*/
#include "Entity.hpp"
#include "GraphicObject.hpp"
#include "game/Game.hpp"
#include "Save.hpp"
#include "DataPack.hpp"

Entity::Entity(Game *master, std::shared_ptr<GraphicMgr> &mgr, unsigned char typeID, bool grabbed) :
    typeID(typeID), graphic(std::make_shared<GraphicObject>(mgr, 0, 0, grabbed)), master(master)
{
}

Entity::Entity(Game *master, const EntityData &data) :
    typeID(data.typeID), graphic(std::make_shared<GraphicObject>(data.graphic)), alive(data.alive), x(data.x), y(data.y), master(master),
    smoothX(data.mov[0]), smoothY(data.mov[1]), relX(data.mov[2]), relY(data.mov[3]),
    duration(data.duration)
{
}

Entity::~Entity() {}

bool Entity::move(int x, int y, int duration)
{
    for (auto &v : master->whatHere(x, y)) {
        if (collWith(*v))
            return (false);
    }
    auto tmp = list;
    putAt(x, y, duration);
    ignore = list >= tmp;
    fullDuration = duration;
    return (true);
}

bool Entity::update()
{
    if (ignore) {
        ignore = false;
        return (true);
    }
    if (duration) {
        smoothX += relX;
        smoothY += relY;
        graphic->setPosition(smoothX, smoothY);
        --duration;
    }
    if (alive && onUpdate())
        return (true);
    graphic->forceUpdate();
    return (false);
}

void Entity::draw()
{
    graphic->draw();
}

void Entity::putAt(int _x, int _y, int _duration)
{
    duration = _duration;
    x = _x;
    y = _y;
    if (duration) {
        relX = (x - smoothX) / duration;
        relY = (y - smoothY) / duration;
    } else {
        smoothX = x;
        smoothY = y;
        graphic->setPosition(x, y, 0.2 * (typeID == TypeID::BONUS));
    }
    list = master->place(handle.lock(), x, y);
}

EntityData Entity::save() const
{
    return (EntityData({graphic->save(), x, y, {smoothX, smoothY, relX, relY}, duration, alive, typeID}));
}

void Entity::save(Save &game) const
{
    DataPack<EntityData>(game["Entity"]).push(save());
}

void Entity::place()
{
    list = master->place(handle.lock(), x, y);
}

void Entity::loadAll(Game *master, Save &game)
{
    EntityData tmp;
    DataPack<EntityData> datas(game["Entity"]);

    while (datas.pop(tmp)) {
        Entity::load<Entity>(master, tmp);
    }
}

void Entity::animOverride(std::vector<std::shared_ptr<GraphicObject>> &anim)
{
    if (anim.empty())
        return;
    auto tmp = graphic;
    graphic = anim[(duration - 1) * anim.size() / fullDuration];
    graphic->useTransform(*tmp);
}
