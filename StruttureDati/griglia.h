#ifndef GRIGLIA_H
#define GRIGLIA_H

#include "cella.h"

#define MATRIX_DIM 3

class griglia
{
public:
	griglia();
	virtual ~griglia(){};

	void print();
	//void printDebug();
	bool setSymbol(int row, int col, simboli_t simb);
	simboli_t getSymbol(int row, int col);

	bool isFilled();
	bool isAnyTris();

	bool firstEmptyCell(int & row, int & col);

private:
	bool checkRange(int row, int col);
	void clear();
	bool isAnyRowTris();
	bool isAnyColumnTris();
	bool isAnyDiagonalTris();

	cella celle[MATRIX_DIM][MATRIX_DIM];
};

#endif // GRIGLIA_H
