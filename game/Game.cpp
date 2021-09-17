/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Game.cpp
*/
#include "Game.hpp"
#include "Engine/GraphicMgr.hpp"
#include "Engine/Entity.hpp"
#include "Save.hpp"
#include "localTools/Sound.hpp"
#include "localTools/Music.hpp"
#include "localTools/ScoreBoard.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Bonus.hpp"
#include "Explosion.hpp"
#include "Block.hpp"
#include "DataPack.hpp"
#include <cstring>
#include <chrono>
#include <thread>

Game::Game(Save &game, Save &settings) : dist(0.0, 1.0), game(game), settings(settings),
    tex0(LoadTexture("resources/texture/buttons/Resume.png")), tex1(LoadTexture("resources/texture/buttons/Leave-to-menu-without-saving.png")), tex2(LoadTexture("resources/texture/buttons/Save-and-leave-to-menu.png")),
    clic(std::make_shared<lt::Sound>((std::string) "clic.mp3", 1)),
    button0(*this, 0.5, 0.4, tex0, clic, &Game::resume),
    button1(*this, 0.5, 0.5, tex1, clic, &Game::quitWithoutSaving),
    button2(*this, 0.5, 0.6, tex2, clic, &Game::saveAndQuit)
{
    checkX[1] = 1;
    checkX[2] = 1;
    checkY[1] = 1;
    checkY[2] = 1;
    scoreboard = std::make_unique<ScoreBoard>(0);
}

Game::~Game()
{
    uninit();
}

void Game::saveDefault()
{
    settings.save("texStrongWall", "bedrock.obj", 11);
    settings.save("texWeakWall", "dirt.obj", 8);
    settings.save("texBomb", "tnt.obj", 7);
    settings.save("texExplosion", "explosion.obj", 13);
    settings.save("texPlayer", "#steve", 6);
    settings.save("texPlayer2", "#alex", 5);
    settings.save("texPlayer3", "#fox", 4);
    settings.save("texPlayer4", "#other", 6);
    settings.save("texBonusSpeed", "speed.png", 9);
    settings.save("texBonusBomb", "bomb_up.png", 11);
    settings.save("texBonusPower", "fire.png", 8);
    settings.save("texBonusWP", "soft_block_pass.png", 19);
    settings.save("texBackground", "resources/texture/ground.png", 29);
    settings.save("takeBonus", "bonus.mp3", 9);
    settings.save("walk", "footsteps.mp3", 13);
    settings.save("placeBomb", "wall_hit.mp3", 12);
    settings.save("collide", "wall_hit.mp3", 12);
    settings.save("explode", "bomb_explosion.mp3", 18);
    settings.save("music", "resources/audio/bomberman.mp3", 29);
    settings.save("font", "resources/font/minecraft_font.ttf", 33);
}

void Game::init()
{
    uninit();
    initialized = true;
    alive = true;
    active = true;
    settings.load("size", &width);
    if (settings.load("screenshotCount", &nbScreenshot) == 0)
        saveDefault();
    grid.resize(width * height);
    memset(checkX + 3, 0, width - 6);
    memset(checkY + 3, 0, height - 6);
    checkX[width - 3] = 1;
    checkX[width - 2] = 1;
    checkY[height - 3] = 1;
    checkY[height - 2] = 1;
    createBackground();

    strongWall = GraphicMgr::getMgr({settings["texStrongWall"].data(), settings["texStrongWall"].size()});
    weakWall = GraphicMgr::getMgr({settings["texWeakWall"].data(), settings["texWeakWall"].size()});
    bomb = GraphicMgr::getMgr({settings["texBomb"].data(), settings["texBomb"].size()});
    explosion = GraphicMgr::getMgr({settings["texExplosion"].data(), settings["texExplosion"].size()});
    player[0] = GraphicMgr::getMgr({settings["texPlayer"].data(), settings["texPlayer"].size()});
    player[1] = GraphicMgr::getMgr({settings["texPlayer2"].data(), settings["texPlayer2"].size()});
    player[2] = GraphicMgr::getMgr({settings["texPlayer3"].data(), settings["texPlayer3"].size()});
    player[3] = GraphicMgr::getMgr({settings["texPlayer4"].data(), settings["texPlayer4"].size()});
    bonus[Bonus::BOMB_UP] = GraphicMgr::getMgr({settings["texBonusBomb"].data(), settings["texBonusBomb"].size()});
    bonus[Bonus::SPEED_UP] = GraphicMgr::getMgr({settings["texBonusSpeed"].data(), settings["texBonusSpeed"].size()});
    bonus[Bonus::FIRE_UP] = GraphicMgr::getMgr({settings["texBonusPower"].data(), settings["texBonusPower"].size()});
    bonus[Bonus::WALL_PASS] = GraphicMgr::getMgr({settings["texBonusWP"].data(), settings["texBonusWP"].size()});

    takeBonus = std::make_unique<lt::Sound>(std::string({settings["takeBonus"].data(), settings["takeBonus"].size()}), 4);
    walk = std::make_unique<lt::Sound>(std::string({settings["walk"].data(), settings["walk"].size()}), 4);
    placeBomb = std::make_unique<lt::Sound>(std::string({settings["placeBomb"].data(), settings["placeBomb"].size()}), 4);
    collide = std::make_unique<lt::Sound>(std::string({settings["collide"].data(), settings["collide"].size()}), 2);
    explode = std::make_unique<lt::Sound>(std::string({settings["explode"].data(), settings["explode"].size()}), 12);
    // readyGo = std::make_unique<lt::Sound>(std::string({settings["readyGo"].data(), settings["readyGo"].size()}), 1);
    music = std::make_unique<lt::Music>(std::string({settings["music"].data(), settings["music"].size()}), true);
}

void Game::createBackground()
{
    Mesh mesh = {};

    mesh.triangleCount = 2;
    mesh.vertexCount = mesh.triangleCount * 3;
    mesh.vertices = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float *) MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.normals = (float *) MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    // 0 1 2 0 2 3
    mesh.texcoords[0] = mesh.texcoords[6] = 0;
    mesh.texcoords[1] = mesh.texcoords[7] = 0;
    mesh.texcoords[4] = mesh.texcoords[8] = width / 2.f;
    mesh.texcoords[5] = mesh.texcoords[9] = height / 2.f;
    mesh.texcoords[2] = mesh.texcoords[0];
    mesh.texcoords[3] = mesh.texcoords[5];
    mesh.texcoords[10] = mesh.texcoords[4];
    mesh.texcoords[11] = mesh.texcoords[1];
    for (int i = 0; i < 6; ++i) {
        mesh.normals[i * 3 + 0] = 0;
        mesh.normals[i * 3 + 1] = 1;
        mesh.normals[i * 3 + 2] = 0;
        mesh.vertices[i * 3 + 0] = mesh.texcoords[i * 2 + 0] * 2;
        mesh.vertices[i * 3 + 1] = -0.01;
        mesh.vertices[i * 3 + 2] = mesh.texcoords[i * 2 + 1] * 2;
    }
    UploadMesh(&mesh, false);
    background = LoadModelFromMesh(mesh);
    backgroundTex = LoadTexture(settings["texBackground"].data());
    SetTextureWrap(backgroundTex, TEXTURE_WRAP_REPEAT);
    background.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = backgroundTex;
}

void Game::uninit()
{
    if (initialized) {
        settings.save("screenshotCount", &nbScreenshot, 4);
        UnloadTexture(backgroundTex);
        UnloadModel(background);
        explosion.reset();
        GraphicMgr::unload();
        grid.clear();
        initialized = false;
    }
}

void Game::load()
{
    GraphicMgr::loadRef(game);
    Entity::loadAll(this, game);
    Block::loadAll(this, game);
    Bonus::loadAll(this, game);
    { // Player loading
        PlayerData tmp;
        DataPack<PlayerData> datas(game["Player"]);

        while (datas.pop(tmp)) {
            players.push_back(Entity::load<Player>(this, tmp, bomb.lock(),
                walk.get(), placeBomb.get(), takeBonus.get(), collide.get()));
        }
    }
    Bomb::loadAll(this, game);
}

void Game::save()
{
    game.truncate();
    GraphicMgr::saveRef(game);
    for (auto &l : grid) {
        for (auto &v : l) {
            v->save(game);
        }
    }
    game.store();
}

void Game::mainloop()
{
    alive = true;
    active = true;
    grid.clear();
    grid.resize(width * height);
    players.clear();
    if (game["Player"].empty())
        generate();
    else
        load();

    auto delay = std::chrono::duration<int, std::ratio<1,1000000>>(1000000 / 60);
    auto clock = std::chrono::system_clock::now();
    music->start();
    int framecheck = 0;
    while (alive && !WindowShouldClose()) {
        if (!(++framecheck & 0x10))
            clock = std::chrono::system_clock::now();
        clock += delay;
        globalUpdate();
        if (active)
            update();
        draw();
        if (!active)
            pauseUpdate();
        GraphicMgr::endDraw();
        std::this_thread::sleep_until(clock);
    }
    music->stop();
    walk->stopAll();
    placeBomb->stopAll();
    explode->stopAll();
    takeBonus->stopAll();
    collide->stopAll();
    if (!alive) {
        switch (winner) {
            case -3:
                return;
            case -2:
                return save();
            case -1:
                std::cout << "You lost !\n";
                break;
            default:
                std::cout << "Player " << (winner + 1) << " won !\n";
        }
        game.truncate();
        game.store();
    } else
        return save();
}

void Game::globalUpdate()
{
    std::string str = "screenshot ";

    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P)) {
        if (active) {
            walk->pauseAll();
            placeBomb->pauseAll();
            explode->pauseAll();
            takeBonus->pauseAll();
            collide->pauseAll();
            music->pause();
            active = false;
        } else {
            walk->unpauseAll();
            placeBomb->unpauseAll();
            explode->unpauseAll();
            takeBonus->unpauseAll();
            collide->unpauseAll();
            music->unpause();
            active = true;
        }
    }
    if (IsKeyPressed(KEY_F12)) {
        str += std::to_string(++nbScreenshot) + ".png";
        TakeScreenshot(str.c_str());
    }
    char alivePlayerCount = 0;
    char aliveRealPlayerCount = 0;
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->isAlive()) {
            ++alivePlayerCount;
            if (players[i]->isConnected()) {
                winner = i;
                ++aliveRealPlayerCount;
            }
        }
    }
    if (aliveRealPlayerCount == 0) {
        winner = -1;
        alive = false;
    }
    if (alivePlayerCount == 1)
        alive = false;
    music->update();
}

void Game::update()
{
    for (auto &l : grid) {
        for (auto it = l.begin(); it != l.end();) {
            if ((*it)->update()) {
                ++it;
            } else {
                l.erase(it++);
            }
        }
    }
}

void Game::draw()
{
    float pos = 45.f;

    GraphicMgr::startDraw(camera);
    ClearBackground({});
    DrawModel(background, {-0.5, 0, -0.5}, 1.f, WHITE);
    for (auto &l : grid) {
        for (auto &v : l) {
            v->draw();
        }
    }
    GraphicMgr::draw();

    scoreboard->print_background(1618.f, 0.f);
    int i = 0;
    Color c;
    for (auto &p : players) {
        switch (i++) {
            case 0:
                scoreboard->print_skin_kevin(1650.f, pos);
                c = RAYWHITE;
                break;
            case 1:
                scoreboard->print_skin_alex(1650.f, pos);
                c = SKYBLUE;
                break;
            case 2:
                scoreboard->print_skin_fox(1650.f, pos);
                c = Color({247, 77, 89, 255});
                break;
            case 3:
                scoreboard->print_skin_black(1650.f, pos);
                c = GREEN;
                break;
        }
        DrawTextEx(scoreboard->ret_font(), TextFormat("Score %08i", p->getScore()), Vector2({1650.f, pos + 102}), (float)scoreboard->ret_font().baseSize - 7, 2, c);
        scoreboard->print_bomb_up(1650.f, pos + 130);
        DrawTextEx(scoreboard->ret_font(), TextFormat("%i", p->getRemainingBombs()), Vector2({1700.f, pos + 132}), (float)scoreboard->ret_font().baseSize - 7, 2, c);
        scoreboard->print_speed(1650.f, pos + 170);
        DrawTextEx(scoreboard->ret_font(), TextFormat("%01.02f", p->getSpeed()), Vector2({1700.f, pos + 172}), (float)scoreboard->ret_font().baseSize - 7, 2, c);
        scoreboard->print_fire(1650.f, pos + 210);
        DrawTextEx(scoreboard->ret_font(), TextFormat("%i", p->getBombPower()), Vector2({1700.f, pos + 212}), (float)scoreboard->ret_font().baseSize - 7, 2, c);
        pos += 250.f;
    }
}

std::list<std::shared_ptr<Entity>> *Game::place(std::shared_ptr<Entity> entity, int x, int y)
{
    auto &list = grid[x + y * width];

    list.push_back(entity);
    return (&list);
}

void Game::makeExplosion(Player *owner, int x, int y, int power)
{
    explode->start();
    makeExplosionLine(owner, x - 1, y, 1, true, 1);
    Entity::create<Explosion>(this, explosion, x, y, false);
    makeExplosionLine(owner, x, y, 1, true, power);
    makeExplosionLine(owner, x, y, -1, true, power);
    makeExplosionLine(owner, x, y, 1, false, power);
    makeExplosionLine(owner, x, y, -1, false, power);
}

void Game::makeExplosionLine(Player *owner, int x, int y, int dir, bool xAxis, int range)
{
    while (range--) {
        if (xAxis) {
            x += dir;
        } else {
            y += dir;
        }
        for (auto &v : grid[x + y * width]) {
            switch (v->typeID) {
                case TypeID::SOLID_BLOCK:
                    range = 0;
                    return;
                case TypeID::BOMB:
                    dynamic_cast<Bomb &>(*v).detonate();
                    range = 0;
                    break;
                case TypeID::BREAKABLE_BLOCK:
                    dynamic_cast<Block &>(*v).destroy();
                    owner->addScore(10);
                    range = 0;
                    break;
                case TypeID::PLAYER:
                    owner->addScore(dynamic_cast<Player &>(*v).getScore() / 10);
                    dynamic_cast<Player &>(*v).kill();
                    range = 0;
                    break;
                default:;
            }
        }
        Entity::create<Explosion>(this, explosion, x, y, xAxis);
    }
}

void Game::maybePutBonus(int x, int y)
{
    float randomized = dist(rd);

    if (randomized < 0.2) {
        auto tmp = bonus[(int) (randomized / 0.065)].lock();
        Entity::create<Bonus>(this, tmp, x, y, (Bonus::Type) (randomized / 0.065));
    }
}

std::list<std::shared_ptr<Entity>> &Game::whatHere(int x, int y)
{
    return (grid[x + y * width]);
}

Player *Game::getPlayer(int id)
{
    for (auto &p : players) {
        if (p->getLink() == id)
            return (p.get());
    }
    return (nullptr);
}

void Game::generate()
{
    auto tmp = strongWall.lock();
    auto tmp2 = weakWall.lock();
    auto p0 = player[0].lock();
    auto p1 = player[1].lock();
    auto p2 = player[2].lock();
    auto p3 = player[3].lock();

    players.push_back(Entity::create<Player>(this, p0, 1, 1, bomb.lock(),
        walk.get(), placeBomb.get(), takeBonus.get(), collide.get(), -1));
    players.push_back(Entity::create<Player>(this, p1, width - 2, 1, bomb.lock(),
        walk.get(), placeBomb.get(), takeBonus.get(), collide.get(), 0));
    players.push_back(Entity::create<Player>(this, p2, 1, height - 2, bomb.lock(),
        walk.get(), placeBomb.get(), takeBonus.get(), collide.get(), 1));
    players.push_back(Entity::create<Player>(this, p3, width - 2, height - 2, bomb.lock(),
        walk.get(), placeBomb.get(), takeBonus.get(), collide.get(), 2));
    for (int i = 0; i < width; ++i) {
        Entity::create<Entity>(this, tmp, i, 0, TypeID::SOLID_BLOCK);
        Entity::create<Entity>(this, tmp, i, height - 1, TypeID::SOLID_BLOCK);
    }
    for (int i = 1; i < height - 1; ++i) {
        if (i & 1) {
            Entity::create<Entity>(this, tmp, 0, i, TypeID::SOLID_BLOCK);
            for (int j = 1; j < width - 1; ++j) {
                if (j & 1) {
                    if (dist(rd) < 0.8 && validPos(j, i))
                        Entity::create<Block>(this, tmp2, j, i);
                } else {
                    if (dist(rd) < 0.5 && validPos(j, i))
                        Entity::create<Block>(this, tmp2, j, i);
                }
            }
            Entity::create<Entity>(this, tmp, width - 1, i, TypeID::SOLID_BLOCK);
        } else {
            for (int j = 0; j < width; ++j) {
                if (j & 1) {
                    if (dist(rd) < 0.5 && validPos(j, i))
                        Entity::create<Block>(this, tmp2, j, i);
                } else
                    Entity::create<Entity>(this, tmp, j, i, TypeID::SOLID_BLOCK);
            }
        }
    }
}

bool Game::validPos(int x, int y)
{
    return !(checkX[x] & checkY[y]);
}

void Game::saveAndQuit()
{
    alive = false;
    winner = -2;
}

void Game::quitWithoutSaving()
{
    alive = false;
    winner = -3;
}

void Game::pauseUpdate()
{
    if (IsMouseButtonPressed(0)) {
        button0.clicPressed();
        button1.clicPressed();
        button2.clicPressed();
    }
    if (IsMouseButtonReleased(0)) {
        button0.clicReleased();
        button1.clicReleased();
        button2.clicReleased();
    }
    button0.update();
    button1.update();
    button2.update();
}
