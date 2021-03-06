#include "twoPlayerGame.h"
#include "GameManager.h"


#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int twoPlayerGame::_count = 0;

twoPlayerGame::twoPlayerGame(GameManager & manager):
GameBase(manager)
{
	std::cout << "Costruttore twoPlayerGame count = " << ++_count << std::endl;
}

twoPlayerGame::~twoPlayerGame()
{
	std::cout << "Distruttore twoPlayerGame count = " << --_count << std::endl;
}

void twoPlayerGame::play()
{
		simboli_t simbolo;

		_grid.print();

		bool giocatore1 = true;
		bool partitaTerminata = false;

		while(!partitaTerminata)
		{
			int giocatore = giocatore1 ? 1: 2;

			char simb = giocatore1 ? 'O': 'X';

			std::cout << "Giocatore num " << giocatore << " (simbolo " << simb <<")" <<" tocca a te!" << std::endl << std::endl;

			simbolo = (simboli_t)giocatore;

			if(!inserisciMossa(simbolo))
			{
				std::cout << std::endl << "ARRIVEDERCI alla prossima partita" << std::endl;
				return;
			}

			system("clear");

			_grid.print();

			//_grid.printDebug();

			if(_grid.isAnyTris())
			{
				std::cout << "Complimenti Giocatore num " << giocatore << " : hai vinto!!" << std::endl << std::endl;
				partitaTerminata = true;
			}
			else if(_grid.isFilled())
			{
				std::cout << "Partita finita in parità" << std::endl << std::endl;
				partitaTerminata = true;
			}

			giocatore1 = !giocatore1;
		}
}

bool twoPlayerGame::connectUiEvents()
{

}

bool twoPlayerGame::disconnectUiEvents()
{

}


