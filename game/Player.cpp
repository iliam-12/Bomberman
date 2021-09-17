/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Player.cpp
*/
#include "Player.hpp"
#include "Bomb.hpp"
#include "localTools/Sound.hpp"
#include "Engine/GraphicObject.hpp"
#include "Engine/GraphicMgr.hpp"
#include "Bonus.hpp"
#include "Save.hpp"
#include "DataPack.hpp"
#include "Game.hpp"

Player::Player(Game *master, std::shared_ptr<GraphicMgr> &mgr, std::shared_ptr<GraphicMgr> bombMgr, lt::Sound *walk, lt::Sound *placeBomb, lt::Sound *takeBonus, lt::Sound *collide, int gamepad) :
    Entity(master, mgr, TypeID::PLAYER, false), bombMgr(bombMgr), binding(gamepad), walk(walk), placeBomb(placeBomb), takeBonus(takeBonus), collide(collide)
{
    lookAt(Movement::DOWN);
    connected = binding.isConnected();
    anim = mgr->getAnim();
}

Player::Player(Game *master, const PlayerData &data, std::shared_ptr<GraphicMgr> bombMgr, lt::Sound *walk, lt::Sound *placeBomb, lt::Sound *takeBonus, lt::Sound *collide) :
    Entity(master, data.base), bombMgr(bombMgr), killed(data.killed), binding(data.gamepad), duration(data.duration), bombs(data.bombs), bombPower(data.bombPower), bypassing(data.bypassing), collided(data.collided), score(data.score), walk(walk), placeBomb(placeBomb), takeBonus(takeBonus), collide(collide)
{
    lookAt(Movement::DOWN);
    connected = binding.isConnected();
    anim = graphic->getMgr()->getAnim();
}

Player::~Player()
{}

bool Player::collWith(int typeID)
{
    return (typeID + bypassing < TypeID::PLAYER);
}

bool Player::collWith(Entity &other)
{
    if (collWith(other.typeID))
        return (true);
    if (other.typeID == TypeID::BONUS) {
        score += 50;
        switch (dynamic_cast<Bonus &>(other).collect()) {
            case Bonus::BOMB_UP:
                ++bombs;
                break;
            case Bonus::SPEED_UP:
                duration -= duration / 6;
                break;
            case Bonus::FIRE_UP:
                ++bombPower;
                break;
            case Bonus::WALL_PASS:
                bypassing = true;
                break;
        }
        takeBonus->start();
    }
    return (false);
}

bool Player::onUpdate()
{
    if (killed) {
        immobilize();
        // Animated dying sequence
        alive = --killed > 0;
        return (true);
    }
    if (isIdle()) {
        if (connected) {
            if (binding.putBomb() && bombs)
                putBomb();
            switch (binding.getMove()) {
                case Movement::LEFT:
                    lookAt(Movement::LEFT);
                    moveRel(-1, 0);
                    return (collided);
                case Movement::RIGHT:
                    lookAt(Movement::RIGHT);
                    moveRel(1, 0);
                    return (collided);
                case Movement::UP:
                    lookAt(Movement::UP);
                    moveRel(0, -1);
                    return (collided);
                case Movement::DOWN:
                    lookAt(Movement::DOWN);
                    moveRel(0, 1);
                    return (collided);
                default:;
            }
        } else {
            think();
            return (collided);
        }
    } else {
        animOverride(anim);
    }
    return (true);
}

void Player::putBomb()
{
    for (auto &e : *list) {
        if (collWith(e->typeID))
            return;
    }
    placeBomb->start();
    Entity::create<Bomb>(master, bombMgr, x, y, this, &bombs, bombPower);
}

void Player::moveRel(int relX, int relY)
{
    if (move(x + relX, y + relY, duration)) {
        walk->start();
        collided = false;
    } else if (!collided) {
        collide->start();
        collided = true;
    }
}

void Player::lookAt(Movement dir)
{
    if (direction == dir)
        return;
    direction = dir;
    switch (direction) {
        case Movement::DOWN:
            graphic->setRotation(0 * 3.1415926 / 2);
            break;
        case Movement::LEFT:
            graphic->setRotation(1 * 3.1415926 / 2);
            break;
        case Movement::UP:
            graphic->setRotation(2 * 3.1415926 / 2);
            break;
        case Movement::RIGHT:
            graphic->setRotation(3 * 3.1415926 / 2);
            break;
        default:;
    }
}

void Player::save(Save &game) const
{
    DataPack<PlayerData>(game["Player"]).push({Entity::save(), killed, binding.getGamepad(), duration, bombs, bombPower, score, bypassing, collided});
}

int Player::getLink() const
{
    return (binding.getGamepad());
}

void Player::addScore(int gain)
{
    score += gain;
}

void Player::think()
{
    unsigned char leftRange = 0;
    unsigned char upRange = 0;
    unsigned char rightRange = 0;
    unsigned char downRange = 0;
    const TypeID left = checkRay(x, y, -1, 0, leftRange);
    const TypeID up = checkRay(x, y, 0, -1, upRange);
    const TypeID right = checkRay(x, y, 1, 0, rightRange);
    const TypeID down = checkRay(x, y, 0, 1, downRange);
    char check = (leftRange > 0) | ((upRange > 0) << 1) | ((rightRange > 0) << 2) | ((downRange > 0) << 3);
    char caution = (left != TypeID::BOMB || !isDangerous(x - leftRange - 1, y, leftRange)) | ((up != TypeID::BOMB || !isDangerous(x, y - upRange - 1, upRange)) << 1)
        | ((right != TypeID::BOMB || !isDangerous(x + rightRange + 1, y, rightRange)) << 2) | ((down != TypeID::BOMB || !isDangerous(x, y + downRange + 1, downRange)) << 3);
    char danger = (left != TypeID::BOMB || !isDangerous(x - leftRange - 1, y, leftRange + 1)) | ((up != TypeID::BOMB || !isDangerous(x, y - upRange - 1, upRange + 1)) << 1)
        | ((right != TypeID::BOMB || !isDangerous(x + rightRange + 1, y, rightRange + 1)) << 2) | ((down != TypeID::BOMB || !isDangerous(x, y + downRange + 1, downRange + 1)) << 3);
    char bigDanger = (left != TypeID::BOMB || !isDangerous(x - leftRange - 1, y, leftRange + 2)) | ((up != TypeID::BOMB || !isDangerous(x, y - upRange - 1, upRange + 2)) << 1)
        | ((right != TypeID::BOMB || !isDangerous(x + rightRange + 1, y, rightRange + 2)) << 2) | ((down != TypeID::BOMB || !isDangerous(x, y + downRange + 1, downRange + 2)) << 3);
    char prevCheck = check & danger;
    if (!prevCheck)
        return decideOf(check, leftRange, upRange, rightRange, downRange);
    check &= caution;
    if (!check)
        return moveTo(Movement::IDLE);
    prevCheck = check;
    check &= (bigDanger >> 2) | (bigDanger << 2);
    if (!check) {
        // We must escape
        if (prevCheck & 1)
            check |= (moveSafety(x, y, -1, 0)) << 0;
        if (prevCheck & 2)
            check |= (moveSafety(x, y, 0, -1)) << 1;
        if (prevCheck & 4)
            check |= (moveSafety(x, y, 1, 0)) << 2;
        if (prevCheck & 8)
            check |= (moveSafety(x, y, 0, 1)) << 3;
        if (!check)
            return decideOf(prevCheck, leftRange, upRange, rightRange, downRange);
        return decideOf(check, leftRange, upRange, rightRange, downRange);
    }
    char mask = 0;
    prevCheck = check;
    if (prevCheck & 1)
        mask |= (moveSafety(x, y, -1, 0)) << 0;
    if (prevCheck & 2)
        mask |= (moveSafety(x, y, 0, -1)) << 1;
    if (prevCheck & 4)
        mask |= (moveSafety(x, y, 1, 0)) << 2;
    if (prevCheck & 8)
        mask |= (moveSafety(x, y, 0, 1)) << 3;
    check &= mask;
    if (!check) {
        if (danger == 0xf)
            return moveTo(Movement::IDLE);
        return decideOf(prevCheck, leftRange, upRange, rightRange, downRange);
    }
    prevCheck = check;
    check &= (left == TypeID::BONUS) | ((up == TypeID::BONUS) << 1) | ((right == TypeID::BONUS) << 2) | ((down == TypeID::BONUS) << 3);
    if (check)
        return decideOf(check, leftRange, upRange, rightRange, downRange);
    const char targets = ((left == TypeID::BREAKABLE_BLOCK || left == TypeID::PLAYER) && leftRange < bombPower) + ((up == TypeID::BREAKABLE_BLOCK || up == TypeID::PLAYER) && upRange < bombPower) + ((right == TypeID::BREAKABLE_BLOCK || right == TypeID::PLAYER) && rightRange < bombPower) + ((down == TypeID::BREAKABLE_BLOCK || down == TypeID::PLAYER) && downRange < bombPower);
    if (targets && (danger == 0xf))
        return decideOf(prevCheck, leftRange, upRange, rightRange, downRange, targets);
    check = prevCheck & ((left == TypeID::BREAKABLE_BLOCK || left == TypeID::PLAYER) | ((up == TypeID::BREAKABLE_BLOCK || up == TypeID::PLAYER) << 1) | ((right == TypeID::BREAKABLE_BLOCK || right == TypeID::PLAYER) << 2) | ((down == TypeID::BREAKABLE_BLOCK || down == TypeID::PLAYER) << 3));
    if (!check)
        return decideOf(prevCheck, leftRange, upRange, rightRange, downRange);
    if (danger != bigDanger) {
        prevCheck = check;
        check &= (leftRange > 1) | ((upRange > 1) << 1) | ((rightRange > 1) << 2) | ((downRange > 1) << 3);
        if (!check)
            return decideOf(prevCheck, -leftRange, -upRange, -rightRange, -downRange);
    }
    return decideOf(check, -leftRange, -upRange, -rightRange, -downRange);
}

TypeID Player::checkRay(int x, int y, int relX, int relY, unsigned char &range)
{
    TypeID ret = (TypeID) 0;

    while (1) {
        x += relX;
        y += relY;
        auto &tmp = master->whatHere(x, y);
        for (auto &v : tmp) {
            if (!ret)
                ret = (TypeID) v->typeID;
            if (v->typeID <= TypeID::PLAYER) {
                if (v->typeID == TypeID::BOMB)
                    return (TypeID::BOMB);
                return (ret);
            }
        }
        ++range;
    }
}

void Player::moveTo(Movement mv)
{
    if (mv == Movement::IDLE) {
        collided = true;
        return;
    }
    lookAt(mv);
    switch (mv) {
        case Movement::LEFT:
            moveRel(-1, 0);
            break;
        case Movement::RIGHT:
            moveRel(1, 0);
            break;
        case Movement::UP:
            moveRel(0, -1);
            break;
        case Movement::DOWN:
            moveRel(0, 1);
            break;
        default:;
    }
}

bool Player::moveSafety(int x, int y, int relX, int relY)
{
    x += relX;
    y += relY;
    return !(isDangerous(x, y, relY, relX) || isDangerous(x, y, -relY, -relX));
}

void Player::decideOf(char c, int l, int u, int r, int d, char bombTargets)
{
    Movement dir = Movement::IDLE;
    int best = -100;

    if (c & 1) {
        dir = Movement::LEFT;
        best = l;
    }
    if ((c & 2) && u > best) {
        dir = Movement::UP;
        best = u;
    }
    if ((c & 4) && r > best) {
        dir = Movement::RIGHT;
        best = r;
    }
    if ((c & 8) && d > best) {
        dir = Movement::DOWN;
        best = d;
    }
    const bool bombing = searchEscape(dir, std::min(best, 150 / duration), bombPower);
    switch (direction) {
        case Movement::LEFT:
            if ((c & 1) && !(bombing && bombOptimal(direction, bombTargets)))
                return moveTo(direction);
            break;
        case Movement::UP:
            if ((c & 2) && !(bombing && bombOptimal(direction, bombTargets)))
                return moveTo(direction);
            break;
        case Movement::RIGHT:
            if ((c & 4) && !(bombing && bombOptimal(direction, bombTargets)))
                return moveTo(direction);
            break;
        case Movement::DOWN:
            if ((c & 8) && !(bombing && bombOptimal(direction, bombTargets)))
                return moveTo(direction);
            break;
        default:;
    }
    if (bombing) {
        if (bombs)
            putBomb();
        else
            return moveTo(Movement::IDLE);
    }
    moveTo(dir);
}

void Player::decideOf(char c, int l, int u, int r, int d)
{
    Movement dir = Movement::IDLE;
    int best = -100;

    if (c & 1) {
        dir = Movement::LEFT;
        best = l;
    }
    if ((c & 2) && u > best) {
        dir = Movement::UP;
        best = u;
    }
    if ((c & 4) && r > best) {
        dir = Movement::RIGHT;
        best = r;
    }
    if ((c & 8) && d > best) {
        dir = Movement::DOWN;
        best = d;
    }
    switch (direction) {
        case Movement::LEFT:
            if (c & 1)
                return moveTo(direction);
            break;
        case Movement::UP:
            if (c & 2)
                return moveTo(direction);
            break;
        case Movement::RIGHT:
            if (c & 4)
                return moveTo(direction);
            break;
        case Movement::DOWN:
            if (c & 8)
                return moveTo(direction);
            break;
        default:;
    }
    moveTo(dir);
}

bool Player::searchEscape(Movement dir, int maxRange, unsigned char range)
{
    int _x = x;
    int _y = y;
    const int relX = (dir == Movement::RIGHT) - (dir == Movement::LEFT);
    const int relY = (dir == Movement::DOWN) - (dir == Movement::UP);
    while (range-- && maxRange--) {
        _x += relX;
        _y += relY;
        unsigned char ray1 = 1;
        unsigned char ray2 = 1;
        if (isDangerous(_x, _y, relY, relX, ray1) || isDangerous(_x, _y, -relY, -relX, ray2))
            return false;
        if ((ray1 | ray2) & 0xfe)
            return (true);
    }
    return (maxRange > 0);
}

bool Player::isDangerous(int x, int y, unsigned char range)
{
    for (auto &v : master->whatHere(x, y)) {
        if (v->typeID == TypeID::BOMB)
            return (range <= dynamic_cast<Bomb &>(*v).getPower());
    }
    return false;
}

bool Player::isDangerous(int x, int y, int relX, int relY)
{
    unsigned char range = 1;

    if (checkRay(x, y, relX, relY, range) == TypeID::BOMB)
        return isDangerous(x + relX * range, y + relY * range, range);
    return false;
}

bool Player::isDangerous(int x, int y, int relX, int relY, unsigned char &range)
{
    if (checkRay(x, y, relX, relY, range) == TypeID::BOMB)
        return isDangerous(x + relX * range, y + relY * range, range);
    return false;
}

bool Player::bombOptimal(Movement dir, char targets)
{
    if (x & y & 1)
        return true;
    const int relX = (dir == Movement::RIGHT) - (dir == Movement::LEFT);
    const int relY = (dir == Movement::DOWN) - (dir == Movement::UP);
    int _x = x + relX;
    int _y = y + relY;
    unsigned char ray = 1;
    switch (checkRay(_x, _y, relY, relX, ray)) {
        case TypeID::PLAYER:
        case TypeID::BREAKABLE_BLOCK:
            targets -= (ray <= bombPower);
            break;
        default:;
    }
    ray = 1;
    switch (checkRay(_x, _y, -relY, -relX, ray)) {
        case TypeID::PLAYER:
        case TypeID::BREAKABLE_BLOCK:
            targets -= (ray <= bombPower);
            break;
        default:;
    }
    return (targets > 0);
}
