#include "GameManager.h"

#include "GameFactory.h"
#include "GameGridView.h"

#include "MyDialog.h"

#include <iostream>
#include <QApplication>

using namespace std;

#define PLAYER1 "player1"
#define PLAYER2 "player2"

GameManager::GameManager():
_dialog(NULL),
_game(NULL),
_gameView(NULL),
_numPlayer(0),
_isInizialized(false),
_isStarted(false),
_gameStarted(false)
{
}

GameManager::~GameManager()
{
	_playerMap.clear();
}

//NOTE: potrebbe essere raffinata per gestire anche gli altri livelli
bool GameManager::checkStartedStatus()
{
	if(!_isInizialized)
	{
		cout << "ERROR GameManager: not initialized" << endl;
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
	
	return true;
}

void GameManager::numPlayerSelectedSlot(int  playerNum)
{
	_dialog->hide();

	startGame(playerNum);
}

void GameManager::startGame(int playerNum)
{
	if(!checkStartedStatus())
		return;


	if(_gameStarted)
	{
		cout << "GameManager::numPlayerSelectedSlot ERRORE game already started = " << endl;
		return;
	}

	_gameView = new GameGridView(*this);

	_game = GameFactory::createGame(*this, playerNum);

	_game->start();
	_gameView->connectData();

	connect(_game, SIGNAL(gameFinished()), this, SLOT(gameFinishedSlot()));

	_gameView->show();

	_gameStarted = true;
}

void GameManager::gameFinishedSlot()
{
	stopGame();
	stop();

	uninit();
	
	//NOTE: porkaround tanto per fare delle prove
	QApplication::exit(0);
}

void GameManager::stopGame()
{
	if(!checkStartedStatus())
		return;

	if(!_gameStarted)
	{
		cout << "GameManager::numPlayerSelectedSlot ERRORE game not started = " << endl;
		return;
	}

	_game->stop();
	_gameView->disconnectData();

	disconnect(_game, SIGNAL(gameFinished()), this, SLOT(gameFinishedSlot()));

	_gameView->hide();

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
	_dialog->deleteLater();
	_gameView->deleteLater();
	
	//NOTE: la uninit viene attualmente invocata a sequito di un evento generato da 
	_game->deleteLater();

	_isInizialized = false;
	
	deleteLater();

	return true;
}

IGameView & GameManager::getView()
{
	return *_gameView;
}

IGame & GameManager::getGame()
{
	return * _game;
}

const QString GameManager::getPlayerSymbol(const QString & playerId) const
{
	if(!_playerMap.contains(playerId))
	{
		cout << "GameManager::getPlayerSymbol ERRORE player not present in map" << endl;
		return _emptySymbol;
	}
	
	return _playerMap[playerId];
}

void GameManager::addPlayerSymbol(const QString & playerId, const QString & symbol)
{
	if(!_playerMap.contains(playerId))
	{
		cout << "GameManager::getPlayerSymbol WARNING player already present in map" << endl;
	}
	
	_playerMap[playerId] = symbol;
}

