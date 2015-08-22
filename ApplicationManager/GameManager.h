#ifndef PLAYMANAGER_H
#define PLAYMANAGER_H

#include <QtCore/QObject>

class GameGridView;
class IGame;
class MyDialog;

class GameManager : public QObject
{
	Q_OBJECT

	public:
		GameManager();
		virtual ~GameManager();

		bool init();
		bool start();
		bool stop();
		bool uninit();

	private Q_SLOTS:
		void	numPlayerSelectedSlot(int);
		void gameFinishedSlot();

	private:
		void startGame(int playerNum);
		void stopGame();
		inline bool checkStartedStatus();

		MyDialog* _dialog;
		IGame* _game;
    int _numPlayer;
		bool _isInizialized;
		bool _isStarted;
		bool _gameStarted;
};

#endif // PLAYMANAGER_H
