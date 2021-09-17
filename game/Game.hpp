/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Game.hpp
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include "Save.hpp"
#include "localTools/Button.hpp"
#include <raylib.h>
#include <random>

class GraphicMgr;
class Entity;
class Player;
class ScoreBoard;

namespace lt {
    class Sound;
    class Music;
};

class Game {
public:
    Game(Save &game, Save &settings);
    virtual ~Game();
    Game(const Game &cpy) = delete;
    Game &operator=(const Game &src) = delete;

    void init(); // Initialize game resources depending on settings content
    void uninit(); // Uninitialize game resources
    void mainloop(); // Start game mainloop depending on game content

    // INTERNAL ONLY
    Player *getPlayer(int id);
    std::list<std::shared_ptr<Entity>> *place(std::shared_ptr<Entity> entity, int x, int y);
    void makeExplosion(Player *owner, int x, int y, int power);
    void maybePutBonus(int x, int y);
    std::list<std::shared_ptr<Entity>> &whatHere(int x, int y); // For AI bot
private:
    std::random_device rd;
    std::uniform_real_distribution<float> dist;
    void makeExplosionLine(Player *owner, int x, int y, int dir, bool xAxis, int range);
    void load();
    void save();
    void update();
    void globalUpdate();
    void draw();
    void generate();
    bool validPos(int x, int y);
    void createBackground();
    void saveDefault();
    Model background;
    Texture2D backgroundTex;
    std::weak_ptr<GraphicMgr> strongWall;
    std::weak_ptr<GraphicMgr> weakWall;
    std::weak_ptr<GraphicMgr> bomb;
    std::shared_ptr<GraphicMgr> explosion; // A line-shaped explosion
    std::weak_ptr<GraphicMgr> player[4];
    std::weak_ptr<GraphicMgr> bonus[4];
    std::unique_ptr<lt::Sound> walk;
    std::unique_ptr<lt::Sound> placeBomb;
    std::unique_ptr<lt::Sound> explode;
    std::unique_ptr<lt::Sound> takeBonus;
    std::unique_ptr<lt::Sound> collide;
    std::unique_ptr<lt::Sound> readyGo;
    std::unique_ptr<lt::Music> music;
    bool initialized = false;
    bool active = true;
    bool alive = true;
    int nbScreenshot = 0;
    char winner = -1;
    Save &game;
    Save &settings;
    Camera camera {{19.1, 24, 25}, {19.1, 0, 25/2. - 0.5}, {0, 1, 0}, 22, CAMERA_ORTHOGRAPHIC}; /*/ CAMERA_PERSPECIVE}; //*/
    std::vector<std::list<std::shared_ptr<Entity>>> grid; // linear 2-dimension grid :)
    std::vector<std::shared_ptr<Player>> players;
    std::unique_ptr<ScoreBoard> scoreboard;
    int width = 33;
    int height = 25;
    unsigned char checkX[127];
    unsigned char checkY[127];
    // pause menu resources
    void pauseUpdate();
    void resume() {active = true;}
    void saveAndQuit();
    void quitWithoutSaving();
    Texture2D tex0;
    Texture2D tex1;
    Texture2D tex2;
    std::shared_ptr<lt::Sound> clic;
    Button<Game> button0;
    Button<Game> button1;
    Button<Game> button2;
};

#endif /* GAME_HPP_ */
