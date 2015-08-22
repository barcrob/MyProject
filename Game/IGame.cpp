#include "IGame.h"

#include <GameManager.h>

#include <iostream>

IGame::IGame(GameManager & manager):
QObject(),
_gameManager(manager)
{

}

IGame::~IGame()
{

}