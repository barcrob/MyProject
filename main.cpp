// #include "twoPlayerGame.h"
// #include "onePlayerGame.h"
#include "GameFactory.h"

#include <readUtility.h>
#include <GameCache.h>

#include "GameManager.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QtGui/QInputDialog>
#include <QStringList>
#include <QDate>
#include <QApplication>

using namespace std;

//COMMENTO PER PROVA GIT
//COMMENTO BIS PER PROVA GIT



//TODO: non più necessario, causa interfaccia grafica
// bool manageEndSession()
// {
// 	bool validResponse = false;
// 
// 	while(!validResponse)
// 	{
// 		std::cout << "Vuoi giocara un'altra partita?" << std::endl << std::endl;
// 		std::cout << "1) Sì" << std::endl;
// 		std::cout << "2) No" << std::endl;
// 
// 		int choice;
// 		if(!readUtility::safeReadInt(choice))
// 		{
// 			std::cout << "Risposta non valida ripetere la selezione" << std::endl;
// 			continue;
// 		}
// 		
// 		if(choice == 1)
// 		{
// 			return false;
// 		}
// 		else if(choice == 2)
// 		{
// 			return true;
// 		}
// 		else
// 		{
// 			std::cout << "Risposta non valida ripetere la selezione" << std::endl;
// 		}
// 	}
// }

//TODO: verificare se è il caso di reintegrare la cache, ma solo dopo aver esteso l'integrazione
//della gui al twoPlayerGame
// void cacheTest()
// {
// 	Griglia g1;
// 	g1.setSymbol(1,1, cerchio);
// 	g1.setSymbol(1,2, croce);
// 	GameCache::insertInCache(g1.serialize(), std::pair<int, int>(2, 2));
// 
// 	std::pair<int, int> choice;
// 	
// 	if(GameCache::getChoice(g1.serialize(), choice))
// 	{
// 		std::cout << std::endl << "row in cache = " << choice.first << std::endl;
// 		std::cout << std::endl << "col in cache = " << choice.second << std::endl;
// 	}
// }


int main(int argc, char **argv) {

	QApplication app(argc, argv);

	GameManager* gameManager = new GameManager();

	gameManager->init();

	gameManager->start();

  return app.exec();
}
