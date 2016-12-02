#ifndef PLAYMANAGER_H
#define PLAYMANAGER_H

#include <QtCore/QObject>
#include <QMap>

class IGameView;
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

		const QString getPlayerSymbol(const QString & playerId) const;

		IGameView & getView();
		IGame & getGame();

	private Q_SLOTS:
		void numPlayerSelectedSlot(int);
		void gameFinishedSlot();

	private:
		void startGame(int playerNum);
		void stopGame();
		inline bool checkStartedStatus();
		void addPlayerSymbol(const QString & playerId, const QString & symbol);

		MyDialog* _dialog;
		IGame* _game;
		IGameView* _gameView;
    int _numPlayer;
		bool _isInizialized;
		bool _isStarted;
		bool _gameStarted;
		QMap<QString, QString> _playerMap;
		QString _emptySymbol;
};

#endif // PLAYMANAGER_H
