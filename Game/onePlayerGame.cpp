#include "onePlayerGame.h"
#include "readUtility.h"

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

bool onePlayerGame::leggiCoordinata(int & coord, coordinateType_t type)
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
					return false;
				}
				else if(coord>0 && coord<=MATRIX_DIM)
				{
					validValue = true;
					return true;
				}
				else
				{
					std::cout << "Valore non valido, riprovare" << std::endl;
				}
			}
			else
			{
				std::cout << "Valore non valido, riprovare" << std::endl;
			}
		}
}

// void onePlayerGame::virtualPlayerChoice()
// {
// 	tryToWin();
// 
// 	playDefense();
// }

// void onePlayerGame::tryToWin()
// {
// 
// }

bool onePlayerGame::inserisciMossa(const simboli_t simbolo)
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

		if(!mossaValida)
		{
			//Ristampo la griglia per dare la possibilità al giocatore di capire meglio
			//dove ha sbagliato e ripetere la selezione
			_grid.print();
		}
	}

	return true;
}

void onePlayerGame::calcolaMossa(simboli_t symb)
{
	std::cout << "calcolaMossa" << std::endl;
	
	int row(0), col(0);

	if(_grid.tryToWin(symb, row, col))
	{
		std::cout << "calcolaMossa trovata mossa vincente su cella (" << row << ","<< col << ")" << std::endl;
	}
	else if(_grid.tryNoLose(symb, row, col))
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