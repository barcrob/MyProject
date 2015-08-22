#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "griglia.h"

#include "IGame.h"

class IGameView;
class GameManager;

typedef enum
{
	rowType,
	columnType
}coordinateType_t;

class GameBase: public IGame
{
	public:
		GameBase(GameManager & manager);
		virtual ~GameBase();

		bool tryToWin(simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryNoLose(simboli_t symb, int & winnerRow, int & winnerColumn);

		bool tryWinnerRowBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerColumnBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerMainDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerSecondaryDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
	
	protected:
		bool inserisciMossa(simboli_t simbolo);
		bool leggiCoordinata(int & coord, coordinateType_t type);

		Griglia _grid;
		IGameView* _gameView;
};

#endif // GAMEBASE_H
