#include "onePlayerGame.h"
#include <GameCache.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int onePlayerGame::_count = 0;

onePlayerGame::onePlayerGame()
{
	std::cout << "Costruttore onePlayerGame count = " << ++_count << std::endl;
}

onePlayerGame::~onePlayerGame()
{
	std::cout << "Distruttore onePlayerGame count = " << --_count << std::endl;
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

	//Provo a vedere se la situazione di gioco è già presente in cache
	QString key = _grid.serialize();
	std::pair<int, int> choice;

	if(GameCache::getChoice(key, choice))
	{
		//Se la situazione di gioco è presente in cache prelevo la mossa
		//in essa contenuta
		std::cout << "mossa prelevata dalla cache" << std::endl;

		row = choice.first;
		col = choice.second;

		_grid.setSymbol(row, col, symb);
		return;
	}

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

/*
 *	Override del metodo della classe GameBase
 */
bool onePlayerGame::inserisciMossa(simboli_t simbolo)
{
	bool mossaValida = false;

	Griglia invertedGrid = _grid.invert();

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
			_grid.print();
		}
 		else
		{
			GameCache::insertInCache(invertedGrid.serialize(), std::pair<int, int>(row-1, col-1));
		}
 			//_mosseCache[invertedGrid.serialize()] = std::pair<int, int>(row-1, col-1);
		//std::cout << "string della griglia = : '" << _grid.serialize().toStdString() << "'" << std::endl;
	}

	return true;
}