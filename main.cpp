/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** main.cpp
*/
#include "menu/Menu.hpp"
#include "Save.hpp"
#include "localTools/Text.hpp"
#include <raylib.h>

#include "game/Game.hpp"
int main(int argc, char const *argv[])
{
    Save settings;

    // Initialization
    settings.open("settings");
    InitWindow(1920, 1080, "Bomberman");
    InitAudioDevice();
    SetWindowMinSize(800, 600);
    ToggleFullscreen();
    SetExitKey(KEY_F4);
    Text::loadFont({settings["font"].data(), settings["font"].size()});
    {
        Menu menu(settings);
        menu.init();
        // Mainloop
        menu.mainloop();
    }
    // Uninitialization
    Text::unloadFont();
    settings.store();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
