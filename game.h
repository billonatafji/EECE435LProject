#ifndef GAME_H
#define GAME_H

#include "scores.h"
#include "user.h"
#include "stdlib.h"

class Game
{
public:
    Game();
    User* user;
    int Difficulty;
    enum GameDifficulty{easy = 1, medium = 2, hard = 3};

    void SetDifficulty(bool easyRadio, bool mediumRadio, bool hardRadio);
};
#endif // GAME_H
