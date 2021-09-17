/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Bonus.hpp
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include "Engine/Entity.hpp"

class Bonus : public Entity {
public:
    enum Type : unsigned char {
        BOMB_UP,
        SPEED_UP,
        FIRE_UP,
        WALL_PASS
    };

    Bonus(Game *master, std::shared_ptr<GraphicMgr> &mgr, enum Type type);
    Bonus(Game *master, const BonusData &data);
    virtual ~Bonus();
    Bonus(const Bonus &cpy) = delete;
    Bonus &operator=(const Bonus &src) = delete;

    virtual void save(Save &game) const override;
    unsigned char collect();
    static void loadAll(Game *master, Save &game);
private:
    const unsigned char type;
};

#endif /* BONUS_HPP_ */
