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

		virtual bool start() = 0;
		virtual bool stop() = 0;

	Q_SIGNALS:
		void gameFinished();
		void symbolSelectedSignal(int row, int col, const QString & symbol);
	
	protected:
		GameManager & _gameManager;
};

#endif // IGAME_H