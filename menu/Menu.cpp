/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** Menu.cpp
*/
#include "Menu.hpp"

Menu::Menu(Save &settingSave) :
    settingSave(settingSave), game(gameSave, settingSave), clic(std::make_shared<lt::Sound>((std::string) "clic.mp3", 1)),
    _cursorBar(LoadTexture("resources/texture/buttons/cursor-bar.png")), _cursors(LoadTexture("resources/texture/buttons/cursors.png")),
    cursor(*this, 0.5, 0.5, 0, "Volume : ", _cursorBar, _cursors, clic, &Menu::setVolume)
{
    settingSave.load("mainVolume", &volume);
    settingSave.load("Fullscreen", &fullscreen);
    settingSave.load("Background", &bg);
    settingSave.load("Texture", &texture);
    setWindow(fullscreen);
    setVolume(volume);
    setTexture(texture);
    cursor.setValue(volume);
    cursor.setPosition(0.5, 0.35);
    Fullscreen.setPosition(0.5, 0.6);
}

Menu::~Menu()
{
    settingSave.save("mainVolume", &volume, sizeof(volume));
    settingSave.save("Fullscreen", &fullscreen, sizeof(fullscreen));
    settingSave.save("Background", &bg, sizeof(bg));
    settingSave.save("Texture", &texture, sizeof(texture));
    game.uninit();
    UnloadTexture(_background);
    UnloadTexture(_background2);
    UnloadTexture(_new);
    UnloadTexture(_load);
    UnloadTexture(_settings);
    UnloadTexture(_help);
    UnloadTexture(_helpText);
    UnloadTexture(_exit);
    UnloadTexture(_back);
    UnloadTexture(_cursorBar);
    UnloadTexture(_cursors);
    UnloadTexture(_togglewindow);
}

void Menu::init()
{
    _background = LoadTexture("resources/texture/labyrinthe-menu.png");
    _background2 = LoadTexture("resources/texture/second-background.png");
    _new = LoadTexture("resources/texture/buttons/New_Game.png");
    _load = LoadTexture("resources/texture/buttons/Load_Game.png");
    _settings = LoadTexture("resources/texture/buttons/Settings.png");
    _help = LoadTexture("resources/texture/buttons/Help.png");
    _helpText = LoadTexture("resources/texture/help_text.png");
    _exit = LoadTexture("resources/texture/buttons/Exit.png");
    _back = LoadTexture("resources/texture/buttons/back.png");
    _togglewindow = LoadTexture("resources/texture/buttons/Fullscreen.png");
}

void Menu::play()
{
    gameSave.truncate();
    game.mainloop();
}

void Menu::quit()
{
    _play = false;
}

void Menu::exit()
{
    if (_settings_menu)
        game.init();
    _help_menu = false;
    _settings_menu = false;
}

void Menu::test()
{
    game.mainloop();
}

void Menu::help()
{
    _help_menu = true;
}

void Menu::setWindow(bool fullscreen)
{
    if (fullscreen == false)
        ToggleFullscreen();
}

void Menu::setVolume(float volume)
{
    this->volume = volume;
    SetMasterVolume(volume);
}

void Menu::toggleWindow()
{
    if (fullscreen == true)
        fullscreen = false;
    else
        fullscreen = true;
    ToggleFullscreen();
}

void Menu::settings()
{
    _settings_menu = true;
    game.uninit();
}

Texture2D Menu::whichBackground()
{
    if (bg == 0)
        return (_background);
    return (_background2);    
}

void Menu::changeBackground()
{
    if (bg == 0)
        bg = 1;
    else
        bg = 0;
}

std::string Menu::whatIsScreen()
{
    if (fullscreen == false)
        return (std::string("current : Window"));
    return (std::string("current : Fullscreen"));
}

std::string Menu::setTexture(int texture)
{
    if (texture == 0) {
        settingSave.save("texBackground", "resources/texture/ground.png", 29);
        return (std::string("current texture : ground"));
    } else
        settingSave.save("texBackground", "resources/texture/magma.png", 28);
    return (std::string("current texture : lava"));
}

void Menu::changeTexture()
{
    if (texture == 0) {
        texture = 1;
        settingSave.save("texBackground", "resources/texture/magma.png", 28);
    }
    else {
        texture = 0;
        settingSave.save("texBackground", "resources/texture/ground.png", 29);
    }
}

void Menu::mainloop()
{
    Button btn_back(*this, 0.5, 0.80, _back, clic, &Menu::exit);
    Button btn_new(*this, 0.5, 0.35, _new, clic, &Menu::play);
    Button btn_load(*this, 0.5, 0.45, _load, clic, &Menu::test);
    Button btn_settings(*this, 0.5, 0.55, _settings, clic, &Menu::settings);
    Button2 btn_window(*this, 0.5, 0.55, Text::CENTER, whatIsScreen(), _togglewindow, clic, &Menu::toggleWindow);
    Button2 btn_bg(*this, 0.5, 0.45, Text::CENTER, std::string("Change Background"), _togglewindow, clic, &Menu::changeBackground);
    Button2 btn_texture(*this, 0.5, 0.65, Text::CENTER, setTexture(texture), _togglewindow, clic, &Menu::changeTexture);
    Button btn_help(*this, 0.5, 0.65, _help, clic, &Menu::help);
    Button btn_exit(*this, 0.5, 0.75, _exit, clic, &Menu::quit);

    gameSave.open("save");
    game.init();
    ClearBackground({});
    while (_play && !WindowShouldClose()){
        BeginDrawing();
        DrawTexture(whichBackground(), 0, 0, RAYWHITE);
        if (_help_menu){
            DrawTexture(_helpText, 660, 400, RAYWHITE);
            if (IsMouseButtonPressed(0))
                btn_back.clicPressed();
            if (IsMouseButtonReleased(0))
                btn_back.clicReleased();
            btn_back.update();
        } else if (_settings_menu) {
            if (fullscreen == false) btn_window.setString(std::string("current : Window"));
            else btn_window.setString(std::string("current : Fullscreen"));
            if (texture == 0) btn_texture.setString(std::string("current texture : ground"));
            else btn_texture.setString(std::string("current texture : lava"));
            cursor.setString(std::string("Volume : ") + std::to_string((int) (this->volume * 100)) + "%");
            if (IsMouseButtonPressed(0)) {
                Fullscreen.setColor(YELLOW);
                cursor.clicPressed();
                btn_window.clicPressed();
                btn_bg.clicPressed();
                btn_texture.clicPressed();
                btn_back.clicPressed();
            }
            if (IsMouseButtonReleased(0)) {
                Fullscreen.setColor(WHITE);
                cursor.clicReleased();
                btn_window.clicReleased();
                btn_bg.clicReleased();
                btn_texture.clicReleased();
                btn_back.clicReleased();
            }
            btn_window.update();
            btn_bg.update();
            btn_texture.update();
            cursor.update();
            btn_back.update();
            Fullscreen.draw();
        } else {
            if (IsMouseButtonPressed(0)) {
                btn_new.clicPressed();
                btn_load.clicPressed();
                btn_settings.clicPressed();
                btn_help.clicPressed();
                btn_exit.clicPressed();
            }
            if (IsMouseButtonReleased(0)) {
                btn_new.clicReleased();
                btn_load.clicReleased();
                btn_settings.clicReleased();
                btn_help.clicReleased();
                btn_exit.clicReleased();
            }
            btn_new.update();
            btn_load.update();
            btn_settings.update();
            btn_help.update();
            btn_exit.update();
        }
        EndDrawing();
        ClearBackground({});
    }
    game.uninit();
}
