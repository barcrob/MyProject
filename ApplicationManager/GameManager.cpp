#include "GameManager.h"

#include "../GameFactory.h"

#include "MyDialog.h"

#include <iostream>
#include <QDesktopWidget>
#include <QApplication>

using namespace std;

#define DIALOG_WITDH 200
#define DIALOG_HEIGHT 100

GameManager::GameManager():
_dialog(NULL),
_game(NULL),
_numPlayer(0),
_isInizialized(false),
_isStarted(false),
_gameStarted(false)
{
}

GameManager::~GameManager()
{
}

//NOTE: potrebbe essere raffinata per gestire anche gli altri livelli
bool GameManager::checkStartedStatus()
{
	if(!_isInizialized)
	{
		cout << "GameManager: already initialized" << endl;
		return false;
	}

	if(!_isStarted)
	{
		cout << "ERROR GameManager: not started" << endl;
		return false;
	}

	return true;
}

bool GameManager::init()
{
	if(_isInizialized)
	{
		cout << "GameManager: already initialized" << endl;
		return false;
	}
	
	_dialog = new MyDialog();
	_dialog->setGeometry(0, QApplication::desktop()->screenGeometry().height()-DIALOG_HEIGHT, DIALOG_WITDH, DIALOG_HEIGHT);

	_isInizialized = true;

	return true;
}


bool GameManager::start()
{
	if(!_isInizialized)
	{
		cout << "GameManager: not initialized" << endl;
		return false;
	}

	if(_isStarted)
	{
		cout << "GameManager: already startd" << endl;
		return false;
	}

	connect(_dialog, SIGNAL(numPlayerSelected(int)), this, SLOT(numPlayerSelectedSlot(int)));

	_dialog->show();

	_isStarted = true;
}

void GameManager::numPlayerSelectedSlot(int  playerNum)
{
	startGame(playerNum);
}

void GameManager::startGame(int playerNum)
{
	if(!checkStartedStatus())
		return;

	_dialog->hide();

	if(_gameStarted)
	{
		cout << "GameManager::numPlayerSelectedSlot ERRORE game already started = " << endl;
		return;
	}

	_game = GameFactory::createGame(*this, playerNum);

	if(!_game->startGame())
	{
		cout << "GameManager::numPlayerSelectedSlot ERRORE in startGame = " << endl;
		return;
	}

	connect(_game, SIGNAL(gameFinished()), this, SLOT(gameFinishedSlot()));
	_gameStarted = true;
}

void GameManager::gameFinishedSlot()
{
	stopGame();
}

void GameManager::stopGame()
{
	if(!checkStartedStatus())
		return;


	if(!_game->stopGame())
	{
		cout << "GameManager::numPlayerSelectedSlot ERRORE in stopGame = " << endl;
		return;
	}

	disconnect(_game, SIGNAL(gameFinished()), this, SLOT(gameFinishedSlot()));
	_gameStarted = false;
}

bool GameManager::stop()
{
	if(!checkStartedStatus())
		return false;

	disconnect(_dialog, SIGNAL(numPlayerSelected(int)), this, SLOT(numPlayerSelectedSlot(int)));

	if(_dialog->isVisible())
	{
		_dialog->hide();
	}

	_isStarted = false;

	return true;
}

bool GameManager::uninit()
{
	delete _game;

	_isInizialized = false;

	return true;
}