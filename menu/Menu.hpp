/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Menu.hpp
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "localTools/Cursor.hpp"
#include "localTools/Button.hpp"
#include "localTools/Button2.hpp"
#include "localTools/Text.hpp"
#include "Save.hpp"
#include "game/Game.hpp"
#include <cstring>

namespace lt {
    class Sound;
};

class Menu {
public:
    Menu() = delete;
    Menu(Save &settingSave);
    virtual ~Menu();
    Menu(const Menu &cpy) = delete;
    Menu &operator=(const Menu &src) = delete;

    void init();
    void mainloop(); // Start menu mainloop
private:
    void play();
    void quit();
    void help();
    void exit();
    void load(/* Add arguments needed */); // Open submenu for selecting save
    void loadSave(/* Add arguments needed */); // Load a save and call startGame
    void settings(/* Add arguments needed */); // Open submenu for settings management
    void startGame(/* Add arguments needed */); // Start the game with parameters
    void test();
    void setVolume(float volume);
    void setWindow(bool fullscreen);
    std::string whatIsScreen();
    void toggleWindow();
    Texture2D whichBackground();
    std::string setTexture(int texture);
    void changeBackground();
    void changeTexture();
    Save &settingSave;
    Save gameSave;
    Game game;
    std::shared_ptr<lt::Sound> clic;
    Texture2D _cursorBar;
    Texture2D _cursors;
    Cursor<Menu> cursor;
    Texture2D _background;
    Texture2D _background2;
    Texture2D _new;
    Texture2D _load;
    Texture2D _settings;
    Texture2D _help;
    Texture2D _helpText;
    Texture2D _exit;
    Texture2D _back;
    Texture2D _togglewindow;
    Text Fullscreen;
    Text Window;
    bool _play = true;
    bool _help_menu = false;
    bool _settings_menu = false;
    bool fullscreen = true;
    float volume = 1;
    int bg = 0;
    int texture = 0;
};

#endif /* MENU_HPP_ */
