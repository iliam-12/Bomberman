/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <list>
#include <vector>
#include "Data.hpp"

class GraphicObject;
class GraphicMgr;
class Game;
class Save;

class Entity {
public:
    virtual ~Entity();
    Entity(const Entity &cpy) = delete;
    Entity &operator=(const Entity &src) = delete;

    template <class T, typename ... Ts>
    static std::shared_ptr<T> create(Game *master, std::shared_ptr<GraphicMgr> &mgr, int x, int y, Ts ... ts)
    {
        auto tmp = std::shared_ptr<T>(new T(master, mgr, ts ...));

        tmp->handle = tmp;
        tmp->putAt(x, y);
        return tmp;
    }
    template <class T, typename Data, typename ... Ts>
    static std::shared_ptr<T> load(Game *master, const Data &data, Ts ... ts)
    {
        auto tmp = std::shared_ptr<T>(new T(master, data, ts ...));

        tmp->handle = tmp;
        tmp->place();
        return tmp;
    }
    const unsigned char typeID;
    bool move(int x, int y, int duration = 0); // Return true on success, false otherwise
    virtual void save(Save &game) const;
    bool update();
    void draw();
    inline bool isIdle() const { // return true if not moving
        return !duration;
    }
    inline void immobilize() {
        duration = 0;
    }
    static void loadAll(Game *master, Save &game);
protected:
    virtual bool collWith(int) {return true;} // Return true if solid by default
    virtual bool collWith(Entity &) {return true;} // Return true if solid
    virtual bool onUpdate() {return true;} // return true to keep or false to remove
    EntityData save() const;
    Entity(Game *master, std::shared_ptr<GraphicMgr> &mgr, unsigned char typeID, bool grabbed = true);
    Entity(Game *master, const EntityData &data);
    void animOverride(std::vector<std::shared_ptr<GraphicObject>> &anim);
    std::shared_ptr<GraphicObject> graphic;
    bool alive = true;
     // Position in grid, do NEVER modify this directly, use move() instead.
    int x, y;
    std::list<std::shared_ptr<Entity>> *list;
    Game *master;
private:
    float smoothX = 0; // smooth X position
    float smoothY = 0; // smooth Y position
    float relX; // relative X movement
    float relY; // relative Y movement
    int duration = 0;
    int fullDuration = 30;
    void putAt(int x, int y, int duration = 0);
    void place();
    bool ignore = false;
    std::weak_ptr<Entity> handle;
};

#endif /* ENTITY_HPP_ */
