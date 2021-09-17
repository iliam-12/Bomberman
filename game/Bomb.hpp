/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Engine/Entity.hpp"
class Player;

class Bomb : public Entity {
public:
    Bomb(Game *master, std::shared_ptr<GraphicMgr> &mgr, Player *owner, int *bombs, int power);
    Bomb(Game *master, const BombData &data);
    virtual ~Bomb();
    Bomb(const Bomb &cpy) = delete;
    Bomb &operator=(const Bomb &src) = delete;

    virtual void save(Save &game) const override;
    void detonate() {lifetime = 1;}
    static void loadAll(Game *master, Save &game);
    int getPower() const {return power;}
protected:
    virtual bool onUpdate() override;
private:
    Player *owner;
    int lifetime = 150;
    int *bombs;
    const int power;
};

#endif /* BOMB_HPP_ */
