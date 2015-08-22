#include "GameFactory.h"

#include "GameManager.h"

#include <onePlayerGame.h>
#include <twoPlayerGame.h>

#include <iostream>

IGame* GameFactory::createGame(GameManager & manager, int gameType)
{
	switch(gameType)
	{
		case 1:
			std::cout << "scelta di un solo giocatore" << std::endl;
			return new onePlayerGame(manager);
			break;

		case 2:
			std::cout << "scelta di due giocatori" << std::endl;
			return new twoPlayerGame(manager);
			break;

		default:
			std::cout << "ERRORE scelta selezionata non valida" << std::endl;
	}
}
