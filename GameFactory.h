#ifndef GAMEFACTOTY_H
#define GAMEFACTOTY_H

#include "IGame.h"

class GameFactory
{
public:
	static IGame* createGame(int gameType);
};

#endif //GAMEFACTOTY_H