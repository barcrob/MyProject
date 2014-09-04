#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include "simboli.h"
#include "IGame.h"


class twoPlayerGame: public IGame
{
public:
	twoPlayerGame();
	virtual ~twoPlayerGame();

	void play();

private:
	bool leggiCoordinata(int & coord, coordinateType_t type);
	bool inserisciMossa(const simboli_t simbolo);
};

#endif // TWOPLAYERGAME_H