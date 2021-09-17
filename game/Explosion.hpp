/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Explosion.hpp
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "Engine/Entity.hpp"

class Explosion : public Entity {
public:
    Explosion(Game *master, std::shared_ptr<GraphicMgr> &mgr, bool xAxis);
    Explosion(Game *master, const EntityData &data);
    virtual ~Explosion();
    Explosion(const Explosion &cpy) = delete;
    Explosion &operator=(const Explosion &src) = delete;

    virtual void save(Save &game) const override;
    static void loadAll(Game *master, Save &game);
protected:
    virtual bool onUpdate() override;
private:
    int lifetime = 10;
};

#endif /* EXPLOSION_HPP_ */
