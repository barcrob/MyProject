#include "twoPlayerGame.h"
#include "readUtility.h"


#include <iostream>
#include <stdlib.h>
#include <stdio.h>

twoPlayerGame::twoPlayerGame()
{

}

twoPlayerGame::~twoPlayerGame()
{

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

bool twoPlayerGame::leggiCoordinata(int & coord, coordinateType_t type)
{
		bool validValue = false;

		while(!validValue)
		{
			std::string coordinata = (type == rowType)? "riga" : "colonna" ;
			std::cout << "Inserire il numero di " << coordinata << " :" << std::endl;
			std::cout << "1)" << std::endl;
			std::cout << "2)" << std::endl;
			std::cout << "3)" << std::endl;
			std::cout << "4) Per uscire dalla partita" << std::endl;

			if(readUtility::safeReadInt(coord))
			{
				if(coord == 4)
				{
					std::cout << "Primo ramo if" << std::endl;
					return false;
				}
				else if(coord>0 && coord<=MATRIX_DIM)
				{
					std::cout << "Secondo ramo if" << std::endl;
					validValue = true;
					return true;
				}
				else
				{
					std::cout << "ramo else" << std::endl;
					std::cout << "Valore non valido, riprovare" << std::endl;
				}
			}
			else
			{
				std::cout << "ramo else" << std::endl;
				std::cout << "Valore non valido, riprovare" << std::endl;
			}
		}
}

bool twoPlayerGame::inserisciMossa(const simboli_t simbolo)
{
	bool mossaValida = false;

	while(!mossaValida)
	{
		std::cout << "Inserisci le coordinate della cella:" << std::endl << std::endl;

		int row = 0;

		if(!leggiCoordinata(row, rowType))
			return false;

		int col = 0;

		if(!leggiCoordinata(col, columnType))
			return false;

		mossaValida = _grid.setSymbol(row-1, col-1, simbolo);

		if(!mossaValida) _grid.print();
	}

	return true;
}
