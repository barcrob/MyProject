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
	bool leggiCoordinata(int & coord, coordinateType_t type);
	bool inserisciMossa(const simboli_t simbolo);
	void calcolaMossa(simboli_t symb);
};

#endif // ONEPLAYERGAME_H