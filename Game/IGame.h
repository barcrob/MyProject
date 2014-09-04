#ifndef IGAME_H
#define IGAME_H

#include "griglia.h"

typedef enum
{
	rowType,
	columnType
}coordinateType_t;

class IGame
{
	public:
		IGame();
		virtual ~IGame();

		virtual void play() = 0;
		//TODO: A spostamento deli metodi che gestiscono la logica del gioco completato aggiungere const al parametro griglia
		bool tryToWin(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryNoLose(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);

		bool tryWinnerRowBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerColumnBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerMainDiagonalBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);
		bool tryWinnerSecondaryDiagonalBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn);

	protected:
		griglia _grid;
};

#endif // IGAME_H
