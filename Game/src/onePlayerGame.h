#ifndef ONEPLAYERGAME_H
#define ONEPLAYERGAME_H

#include "simboli.h"

#include "IGame.h"
#include "GameBase.h"
#include <QTimer>

class GameManager;
class IGameView;

class onePlayerGame: public GameBase
{
	Q_OBJECT

	public:
		onePlayerGame(GameManager & manager);
		virtual ~onePlayerGame();

		bool start();
		bool stop();

	private Q_SLOTS:
		void cellSelectedSlot(int row, int col);
		void timeoutSlot();

	private:
		bool connectUiEvents();
		bool disconnectUiEvents();

		bool isGameFinished();
		void calcolaMossa();

		simboli_t _simboloCorrente;
		static int _count;
		QTimer _waitTimer;
};

#endif // ONEPLAYERGAME_H