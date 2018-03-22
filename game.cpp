#include "game.h"

Game::Game()
{

}

void Game::SetDifficulty(bool easyRadio, bool mediumRadio, bool hardRadio){
    if(easyRadio){
        this->Difficulty = easy;
    }
    else if(mediumRadio){
        this->Difficulty =  medium;
    }
    else if(hardRadio){
        this->Difficulty = hard;
    }
}

