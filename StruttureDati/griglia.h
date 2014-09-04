#ifndef GRIGLIA_H
#define GRIGLIA_H

#include "cella.h"

#define MATRIX_DIM 3

class griglia
{
public:
	griglia();
	//griglia();
	virtual ~griglia(){};

	void print();
	//void printDebug();
	bool setSymbol(int row, int col, simboli_t simb);
	simboli_t getSymbol(int row, int col);

	bool isFilled();
	bool isAnyTris();

	bool tryToWin(simboli_t symb, int & winnerRow, int & winnerColumn);


	bool tryNoLose(simboli_t symb, int & winnerRow, int & winnerColumn);

	bool firstEmptyCell(int & row, int & col);

private:
	bool checkRange(int row, int col);
	void clear();
	bool isAnyRowTris();
	bool isAnyColumnTris();
	bool isAnyDiagonalTris();

	bool tryWinnerRowBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
	bool tryWinnerColumnBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);

	bool tryWinnerMainDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);
	bool tryWinnerSecondaryDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn);

	cella celle[MATRIX_DIM][MATRIX_DIM];
};

#endif // GRIGLIA_H
