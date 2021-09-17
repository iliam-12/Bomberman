/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Block.hpp
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "Engine/Entity.hpp"

class Block : public Entity {
public:
    Block(Game *master, std::shared_ptr<GraphicMgr> &mgr);
    Block(Game *master, const BlockData &data);
    virtual ~Block();
    Block(const Block &cpy) = delete;
    Block &operator=(const Block &src) = delete;

    virtual void save(Save &game) const override;
    void destroy();
    static void loadAll(Game *master, Save &game);
protected:
    virtual bool onUpdate() override;
private:
    int destroyed = 0;
};

#endif /* BLOCK_HPP_ */
