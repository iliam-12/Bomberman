/*
** EPITECH PROJECT, 2021
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** ScoreBoard
*/

#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <raylib.h>

class ScoreBoard {
    public:
        ScoreBoard(int i);
        ~ScoreBoard();

        void print_background(float x, float y);
        void print_skin_kevin(float x, float y);
        void print_skin_alex(float x, float y);
        void print_skin_fox(float x, float y);
        void print_skin_black(float x, float y);
        void print_bomb_up(float x, float y);
        void print_fire(float x, float y);
        void print_speed(float x, float y);
        Font ret_font();

    protected:
    private:
        Texture2D background;
        Texture2D skin_kevin;
        Texture2D skin_alex;
        Texture2D skin_fox;
        Texture2D skin_black;
        Texture2D bomb_up;
        Texture2D fire;
        Texture2D speed;
        Font fontm;
        

        
};

#endif /* !SCOREBOARD_HPP_ */
