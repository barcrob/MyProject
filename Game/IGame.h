#ifndef IGAME_H
#define IGAME_H

#include <QObject>

class GameManager;

class IGame: public QObject
{
	Q_OBJECT

	public:
		IGame(GameManager & gameManager);
		virtual ~IGame();

		virtual bool startGame() = 0;
		virtual bool stopGame() = 0;

	Q_SIGNALS:
		void gameFinished();
	
	protected:
		GameManager & _gameManager;
};

#endif // IGAME_H