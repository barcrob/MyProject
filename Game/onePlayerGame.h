#ifndef ONEPLAYERGAME_H
#define ONEPLAYERGAME_H

#include "simboli.h"

#include "IGame.h"
#include "GameBase.h"

class GameManager;
class IGameView;

class onePlayerGame: public GameBase
{
	Q_OBJECT

	public:
		onePlayerGame(GameManager & manager);
		virtual ~onePlayerGame();

		void play();

		bool startGame();
		bool stopGame();

	protected:
		bool inserisciMossa(simboli_t simbolo);

	private Q_SLOTS:
		void cellSelectedSlot(int row, int col);

	private:
		bool isGameFinished();
		void calcolaMossa(const simboli_t symb);
		void calcolaMossa();

		simboli_t _simboloCorrente;
		bool _giocatore1;
		static int _count;
};

#endif // ONEPLAYERGAME_H