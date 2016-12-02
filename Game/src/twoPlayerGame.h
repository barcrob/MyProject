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

	void play();
	//TODO: implementare per allineare la logica a onePlayer
	bool start(){};
	bool stop(){};
	void setSymbol(int row, int col, const QString symbol){};
	const QString getSymbol(int row, int col) const{};
	


private:
	bool connectUiEvents();
	bool disconnectUiEvents();
	
	static int _count;
};

#endif // TWOPLAYERGAME_H