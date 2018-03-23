/**
* \file Game.cpp
* \brief Game class definition
*
*  the class game is used to select the difficulty of the game
*\author Bilal Natafgi
*\date 21-2-2018
*/

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

