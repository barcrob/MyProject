#include "twoPlayerGame.h"
#include "onePlayerGame.h"
#include "GameFactory.h"

#include <readUtility.h>
#include <GameCache.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

bool manageEndSession()
{
	bool validResponse = false;

	while(!validResponse)
	{
		std::cout << "Vuoi giocara un'altra partita?" << std::endl << std::endl;
		std::cout << "1) Sì" << std::endl;
		std::cout << "2) No" << std::endl;

		int choice;
		if(!readUtility::safeReadInt(choice))
		{
			std::cout << "Risposta non valida ripetere la selezione" << std::endl;
			continue;
		}
		
		if(choice == 1)
		{
			return false;
		}
		else if(choice == 2)
		{
			return true;
		}
		else
		{
			std::cout << "Risposta non valida ripetere la selezione" << std::endl;
		}
	}
}

void cacheTest()
{
	Griglia g1;
	g1.setSymbol(1,1, cerchio);
	g1.setSymbol(1,2, croce);
	GameCache::insertInCache(g1.serialize(), std::pair<int, int>(2, 2));

	std::pair<int, int> choice;
	
	if(GameCache::getChoice(g1.serialize(), choice))
	{
		std::cout << std::endl << "row in cache = " << choice.first << std::endl;
		std::cout << std::endl << "col in cache = " << choice.second << std::endl;
	}
}


int main(int argc, char **argv) {

		system("clear");

		std::cout << std::endl << "GIOCO DEL TRIS" << std::endl;
		std::cout << std::endl << "Premere invio per iniziare una partita" << std::endl;

		char string[256];

		gets(string);

		bool terminateSession = false;

		while(!terminateSession)
		{
			system("clear");

			std::cout << std::endl << "Inserire il numero di giocatori (1,2)" << std::endl;

			int playerNum;
			readUtility::safeReadInt(playerNum);

			IGame* game = GameFactory::createGame(playerNum);

			std::cout << "INIZIO PARTITA" << std::endl << std::endl;
			game->play();
			terminateSession = manageEndSession();

			delete game;
		}

    return 0;
}
