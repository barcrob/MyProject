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

#define WAIT_TIMEOUT 1000

int onePlayerGame::_count = 0;

//NOTE: non c'è bisogno di gestire il passaggio da un giocatore all'altro perchè c'è un giocatore solo
//che è quello che manda gli eventi tramite UI e il computer che invoca calcolaMossa
onePlayerGame::onePlayerGame(GameManager & manager):
GameBase(manager),
_simboloCorrente(vuota)
{
	std::cout << "onePlayerGame Costruttore count = " << ++_count << std::endl;
	
	_waitTimer.setSingleShot(true);
	_waitTimer.setInterval(WAIT_TIMEOUT);
}

onePlayerGame::~onePlayerGame()
{
	std::cout << "onePlayerGame Distruttore count = " << --_count << std::endl;
}

bool onePlayerGame::start()
{
	connectUiEvents();
	
	connect(&_waitTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	return true;
}

bool onePlayerGame::stop()
{
	disconnectUiEvents();
	
	disconnect(&_waitTimer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));

	return true;
}

bool onePlayerGame::connectUiEvents()
{
	std::cout << "onePlayerGame connectUiEvents" << std::endl;
	
	connect(&_gameView, SIGNAL(cellSelectedSignal(int, int)), this, SLOT(cellSelectedSlot(int, int)));

	return true;
}

bool onePlayerGame::disconnectUiEvents()
{
	std::cout << "onePlayerGame::disconnectUiEvents" << std::endl << std::endl;

	disconnect(&_gameView, SIGNAL(cellSelectedSignal(int, int)), this, SLOT(cellSelectedSlot(int, int)));

	return true;
}



void onePlayerGame::cellSelectedSlot(int row, int col)
{
	cout << "onePlayerGame: cellSelectedSlot" << endl;

	if(!_grid.setSymbol(row, col, cerchio))
	{
		cout << "onePlayerGame: ATTENZIONE ERRORE in setSymbol" << endl;
		exit(EXIT_FAILURE);
	}

	symbolSelectedSignal(row, col, QString("O"));

	if(isGameFinished())
	{
		gameFinished();
		return;
	}

	_waitTimer.start();
}

bool onePlayerGame::isGameFinished()
{
	if(_grid.isAnyTris())
	{
		QMessageBox msgBox;
		msgBox.setText("Hai vinto");
		//TODO: provare centramento box
		QSize size = msgBox.size();
		float msgBoxX = _gameView.x()+(_gameView.width()-size.width())/2;
		float msgBoxY = _gameView.y()+(_gameView.height()-size.height())/2;
		msgBox.setGeometry(msgBoxX , msgBoxY, msgBox.width(), msgBox.height() );
		msgBox.exec();
		return true;
	}
	else if(_grid.isFilled())
	{
		QMessageBox msgBox;
		msgBox.setText("Partita finita in parità");

		QSize size = msgBox.size();
		float msgBoxX = _gameView.x()+(_gameView.width()-size.width())/2;
		float msgBoxY = _gameView.y()+(_gameView.height()-size.height())/2;
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
	symbolSelectedSignal(row, col, QString("X"));

	if(win)
	{
		QMessageBox msgBox;
		msgBox.setText("Game Over");

		QSize size = msgBox.size();
		float msgBoxX = _gameView.x()+(_gameView.width()-size.width())/2;
		float msgBoxY = _gameView.y()+(_gameView.height()-size.height())/2;
		msgBox.setGeometry(msgBoxX , msgBoxY, msgBox.width(), msgBox.height() );

		msgBox.exec();
		
		gameFinished();
		return;
	}

	std::cout << endl << endl;
}

void onePlayerGame::timeoutSlot()
{
	calcolaMossa();
}
