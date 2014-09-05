#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "griglia.h"

typedef enum
{
	rowType,
	columnType
}coordinateType_t;

class GameBase
{
	public:
		GameBase();
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
};

#endif // GAMEBASE_H
