/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Engine/Entity.hpp"
#include "Engine/Data.hpp"
#include "inputs/Binding.hpp"
#include <vector>

namespace lt {
    class Sound;
};

class Player : public Entity {
public:
    Player(Game *master, std::shared_ptr<GraphicMgr> &mgr, std::shared_ptr<GraphicMgr> bombMgr, lt::Sound *walk, lt::Sound *placeBomb, lt::Sound *takeBonus, lt::Sound *collide, int gamepad);
    Player(Game *master, const PlayerData &data, std::shared_ptr<GraphicMgr> bombMgr, lt::Sound *walk, lt::Sound *placeBomb, lt::Sound *takeBonus, lt::Sound *collide);
    virtual ~Player();
    Player(const Player &cpy) = delete;
    Player &operator=(const Player &src) = delete;

    inline void kill() {killed = 60;}
    virtual void save(Save &game) const override;

    int getScore() const {return score;}
    void addScore(int gain);
    bool isAlive() const {return alive;}
    bool isConnected() const {return connected;}
    int getRemainingBombs() const {return bombs;}
    int getBombPower() const {return bombPower;}
    float getSpeed() const {return 60. / duration;}

    // INTERNAL ONLY
    int getLink() const;
    int *getBombLink() {return (&bombs);}
protected:
    virtual bool collWith(int typeID) override;
    virtual bool collWith(Entity &other) override;
    virtual bool onUpdate() override;
private:
    void moveRel(int relX, int relY);
    void putBomb();
    void lookAt(Movement dir);
    void think();
    TypeID checkRay(int x, int y, int relX, int relY, unsigned char &range);
    bool moveSafety(int x, int y, int relX, int relY);
    void moveTo(Movement mv);
    void decideOf(char c, int l, int u, int r, int d);
    void decideOf(char c, int l, int u, int r, int d, char bombTargets);
    bool searchEscape(Movement dir, int maxRange, unsigned char range);
    bool isDangerous(int x, int y, unsigned char range);
    bool isDangerous(int x, int y, int relX, int relY);
    bool isDangerous(int x, int y, int relX, int relY, unsigned char &range);
    bool bombOptimal(Movement dir, char targets);
    std::shared_ptr<GraphicMgr> bombMgr;
    std::vector<std::shared_ptr<GraphicObject>> anim;
    int killed = 0;
    Binding binding;
    int duration = 40; // Duration of a movement
    int bombs = 1;
    int bombPower = 1;
    bool bypassing = false; // By default, don't bypass weak walls
    bool collided = false;
    bool connected;
    int score = 0;
    Movement direction = Movement::IDLE;
    lt::Sound *walk;
    lt::Sound *placeBomb;
    lt::Sound *takeBonus;
    lt::Sound *collide;
};

#endif /* PLAYER_HPP_ */
