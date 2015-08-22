#ifndef GAMEFACTOTY_H
#define GAMEFACTOTY_H

#include "IGame.h"

class IGameView;

class GameFactory
{
public:
	static IGame* createGame(GameManager & game, int gameType);
};

#endif //GAMEFACTOTY_H