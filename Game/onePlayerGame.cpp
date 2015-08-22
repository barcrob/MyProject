#include "onePlayerGame.h"

#include <GameCache.h>
#include <IGameView.h>
#include <GameGridView.h>
#include <GameManager.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

using namespace std;

#define WIN_GRID_WITDH 300
#define WIN_GRID_HEIGHT 300

int onePlayerGame::_count = 0;

onePlayerGame::onePlayerGame(GameManager & manager):
GameBase(manager),
_simboloCorrente(vuota),
_giocatore1(true)
{
	std::cout << "onePlayerGame Costruttore count = " << ++_count << std::endl;

	QRectF dim(0,0,WIN_GRID_WITDH, WIN_GRID_HEIGHT );

	_gameView = new GameGridView(dim);
	_gameView->setGeometry(0, QApplication::desktop()->screenGeometry().height()-WIN_GRID_HEIGHT, WIN_GRID_WITDH, WIN_GRID_HEIGHT);
}

onePlayerGame::~onePlayerGame()
{
	std::cout << "onePlayerGame Distruttore count = " << --_count << std::endl;
}

bool onePlayerGame::startGame()
{
	std::cout << "onePlayerGame startGame" << std::endl;
	
	connect(_gameView, SIGNAL(cellSelected(int, int)), this, SLOT(cellSelectedSlot(int, int)));
	_gameView->show();

	return true;
}

bool onePlayerGame::stopGame()
{
	std::cout << "onePlayerGame::stopGame" << std::endl << std::endl;

	_gameView->hide();
	disconnect(_gameView, SIGNAL(cellSelected(int, int)), this, SLOT(cellSelectedSlot(int, int)));

	_gameView->deleteLater();

	return true;
}
/*
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
			std::cout << "calcolaMossa ATTENZIONE non ho trovato nessuna cella vuota" << std::endl;
		}
	}
	
	_grid.setSymbol(row, col, symb);
}
*/

/*
 *	Override del metodo della classe GameBase
 */
/*
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
*/

void onePlayerGame::cellSelectedSlot(int row, int col)
{
	cout << "onePlayerGame: cellSelectedSlot" << endl;

	if(!_giocatore1)
	{
		cout << "onePlayerGame: ATTENZIONE ERRORE in cellSelectedSlot" << endl;
		exit(EXIT_FAILURE);
	}

	if(!_grid.setSymbol(row, col, cerchio))
	{
		cout << "onePlayerGame: ATTENZIONE ERRORE in setSymbol" << endl;
		exit(EXIT_FAILURE);
	}

	_gameView->setSymbol(row, col, QString("O"));

	if(isGameFinished())
	{
		gameFinished();
		return;
	}
	
	_giocatore1 = !_giocatore1;
	calcolaMossa();
}

bool onePlayerGame::isGameFinished()
{
	if(_grid.isAnyTris())
	{
		QMessageBox msgBox;
		msgBox.setText("Hai vinto");
		//TODO: provare centramento box
		QSize size = msgBox.size();
		float msgBoxX = _gameView->x()+(_gameView->width()-size.width())/2;
		float msgBoxY = _gameView->y()+(_gameView->height()-size.height())/2;
		msgBox.setGeometry(msgBoxX , msgBoxY, msgBox.width(), msgBox.height() );
		msgBox.exec();
		return true;
	}
	else if(_grid.isFilled())
	{
		QMessageBox msgBox;
		msgBox.setText("Partita finita in parità");

		QSize size = msgBox.size();
		float msgBoxX = _gameView->x()+(_gameView->width()-size.width())/2;
		float msgBoxY = _gameView->y()+(_gameView->height()-size.height())/2;
		msgBox.setGeometry(msgBoxX , msgBoxY, msgBox.width(), msgBox.height() );
		
		msgBox.exec();
		return true;
	}

	return false;
}

void onePlayerGame::calcolaMossa()
{
	cout << "onePlayerGame: calcolaMossa" << endl;
	
	int row(0), col(0);

	if(_giocatore1)
	{
		cout << "onePlayerGame: ATTENZIONE ERRORE in calcolaMossa" << endl;
		exit(EXIT_FAILURE);
	}

	bool win = false;
	
	if(tryToWin(croce, row, col))
	{
		std::cout << "calcolaMossa trovata mossa vincente su cella (" << row << ","<< col << ")" << std::endl;
		win = true;
	}
	else if(tryNoLose(croce, row, col))
	{
		std::cout << "calcolaMossa trovata mossa vincente per l'avversario su cella (" << row << ","<< col << ")" << std::endl;
	}
	else
	{
		if(!_grid.firstEmptyCell(row, col))
		{
			std::cout << "calcolaMossa ATTENZIONE ERROR non ho trovato nessuna cella vuota" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	_grid.setSymbol(row, col, croce);
	_gameView->setSymbol(row, col, QString("X"));

	if(win)
	{
		QMessageBox msgBox;
		msgBox.setText("Game Over");

		QSize size = msgBox.size();
		float msgBoxX = _gameView->x()+(_gameView->width()-size.width())/2;
		float msgBoxY = _gameView->y()+(_gameView->height()-size.height())/2;
		msgBox.setGeometry(msgBoxX , msgBoxY, msgBox.width(), msgBox.height() );

		msgBox.exec();
		
		gameFinished();
		return;
	}

	_giocatore1 = !_giocatore1;

	std::cout << endl << endl;
}