#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include "simboli.h"
#include "IGame.h"
#include "GameBase.h"


class twoPlayerGame: public IGame, public GameBase
{
public:
	twoPlayerGame();
	virtual ~twoPlayerGame();

	void play();

private:
		static int _count;
};

#endif // TWOPLAYERGAME_H