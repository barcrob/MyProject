#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include "simboli.h"
#include "IGame.h"
#include "GameBase.h"

class IGameView;

class twoPlayerGame: public GameBase
{
public:
	twoPlayerGame(GameManager & manager);
	virtual ~twoPlayerGame();

	virtual  void play();
	//TODO: implementare per allineare la logica a onePlayer
	virtual bool startGame(){};
	virtual bool stopGame(){};
	virtual void setSymbol(int row, int col, const QString symbol){};
	virtual const QString getSymbol(int row, int col) const{};

private:
		static int _count;
};

#endif // TWOPLAYERGAME_H