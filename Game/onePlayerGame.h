#ifndef ONEPLAYERGAME_H
#define ONEPLAYERGAME_H

#include "simboli.h"
#include "IGame.h"
#include "GameBase.h"


class onePlayerGame: public IGame, public GameBase
{
public:
	onePlayerGame();
	virtual ~onePlayerGame();

	void play();

private:
	void calcolaMossa(simboli_t symb);
	static int _count;
};

#endif // ONEPLAYERGAME_H