#ifndef ONEPLAYERGAME_H
#define ONEPLAYERGAME_H

#include "simboli.h"
#include "IGame.h"
#include "GameBase.h"
#include <QHash>


class onePlayerGame: public IGame, public GameBase
{
	public:
		onePlayerGame();
		virtual ~onePlayerGame();

		void play();

	protected:
		bool inserisciMossa(simboli_t simbolo);

	private:
		void calcolaMossa(simboli_t symb);

		static int _count;
		//QHash<QString, std::pair<int, int> > _mosseCache;
};

#endif // ONEPLAYERGAME_H