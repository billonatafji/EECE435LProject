#ifndef GAME_H
#define GAME_H

#include "scores.h"
#include "user.h"
#include "stdlib.h"
#include "gameview.h"

class Game
{
public:
    Game();
    User* user;
    int Difficulty;
    enum GameDifficulty{easy = 1, medium = 2, hard = 3};
    enum GameMode{New = 1, Resume = 2, Over = 3, Win = 4, Pause = 5};
    GameView* gameView;


    void SetDifficulty(bool easyRadio, bool mediumRadio, bool hardRadio);
};
#endif // GAME_H
