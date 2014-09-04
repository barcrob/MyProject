#include "GameFactory.h"

#include <onePlayerGame.h>
#include <twoPlayerGame.h>
#include <iostream>

IGame* GameFactory::createGame(int gameType)
{
	switch(gameType)
	{
		case 1:
			std::cout << "scelta di un solo giocatore" << std::endl;
			return new onePlayerGame();
			break;

		case 2:
			std::cout << "scelta di due giocatori" << std::endl;
			return new twoPlayerGame();
			break;

		default:
			std::cout << "ERRORE scelta selezionata non valida" << std::endl;
	}
}
