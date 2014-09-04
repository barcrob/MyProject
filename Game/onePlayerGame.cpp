#include "onePlayerGame.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

onePlayerGame::onePlayerGame()
{

}

onePlayerGame::~onePlayerGame()
{

}

void onePlayerGame::play()
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

			if(giocatore1)
			{
				if(!inserisciMossa(simbolo))
				{
					std::cout << std::endl << "ARRIVEDERCI alla prossima partita" << std::endl;
					return;
				}
			}
			else
			{
				calcolaMossa(simbolo);
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

void onePlayerGame::calcolaMossa(const simboli_t symb)
{
	std::cout << "calcolaMossa" << std::endl;
	
	int row(0), col(0);

	if(tryToWin(symb, row, col))
	{
		std::cout << "calcolaMossa trovata mossa vincente su cella (" << row << ","<< col << ")" << std::endl;
	}
	else if(tryNoLose(symb, row, col))
	{
		std::cout << "calcolaMossa trovata mossa vincente per l'avversario su cella (" << row << ","<< col << ")" << std::endl;
	}
	else
	{
		if(!_grid.firstEmptyCell(row, col))
		{
			std::cout << "calcolaMossa ATTENZIONE non ho trovato nessauna cella vuota" << std::endl;
		}
	}
	
	_grid.setSymbol(row, col, symb);
}