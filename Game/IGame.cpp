#include "IGame.h"

#include <iostream>

IGame::IGame()
{

}

IGame::~IGame()
{

}

bool IGame::tryToWin(griglia & grid, simboli_t symb, int& winnerRow, int& winnerColumn)
{
	std::cout << "tryToWin" << std::endl;

	if(tryWinnerRowBySimbol(grid, symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente su riga: " << winnerRow << std::endl;
		return true;
	}

	if(tryWinnerColumnBySimbol(grid, symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente su colonna: " << winnerColumn << std::endl;
		return true;
	}

	if(tryWinnerMainDiagonalBySimbol(grid, symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	if(tryWinnerSecondaryDiagonalBySimbol(grid, symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	std::cout << "tryToWin nessuna mossa vincente trovata" << std::endl;

	return false;
}


/*
 * Se trovo una posizione che mi permette di vincere componendo una riga restituisco le coordinate vincenti
 * altrimenti restituisco le ultime coordinate vuote trovate. Per ora non è una tattica intelligente. poi verrà migliorata
 */
bool IGame::tryWinnerRowBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerRowBySimbol" << std::endl;

	int rowIndex = 0;
	int columnIndex = 0;

	for(int i=0;i<MATRIX_DIM;i++)
	{
		int symbCount = 0;

		bool isMissingCellFree = false;

		for(int j=0;j<MATRIX_DIM;j++)
		{
			if(grid.getSymbol(i,j)== symb)
			{
				symbCount++;
			}
			else if(grid.getSymbol(i,j) == vuota)
			{
				isMissingCellFree = true;
				rowIndex = i;
				columnIndex = j;
			}
			else
				continue;
		}

		if((symbCount == 2)&&(isMissingCellFree))
		{
			winnerRow = rowIndex;
			winnerColumn = columnIndex;
			std::cout << "tryWinnerRowBySimbol TROVATA UNA MOSSA VINCENTE NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
			return true;
		}
	}

	return false;
}

bool IGame::tryWinnerColumnBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerColumnBySimbol" << std::endl;

	for(int j=0;j<MATRIX_DIM;j++)
	{
		int symbCount = 0;
		int rowIndex = 0;
		int columnIndex = 0;
		bool isMissingCellFree = false;


		for(int i=0;i<MATRIX_DIM;i++)
		{
			if(grid.getSymbol(i,j) == symb)
			{
				symbCount++;
			}
			else if(grid.getSymbol(i,j) == vuota)
			{
				isMissingCellFree = true;
				rowIndex = i;
				columnIndex = j;
			}
			else
				continue;
		}

		if((symbCount == 2)&&(isMissingCellFree))
		{
			winnerRow = rowIndex;
			winnerColumn = columnIndex;
			std::cout << "tryWinnerColumnBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
			return true;
		}
	}

	return false;
}

bool IGame::tryWinnerMainDiagonalBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerMainDiagonalBySimbol" << std::endl;

	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int i=0;i<MATRIX_DIM;i++)
	{

		if(grid.getSymbol(i,i) == symb)
		{
			symbCount++;
		}
		else if(grid.getSymbol(i,i) == vuota)
		{
			isMissingCellFree = true;
			rowIndex = i;
			columnIndex = i;
		}
		else
			break;
	}

	if((symbCount == 2)&&(isMissingCellFree))
	{
		winnerRow = rowIndex;
		winnerColumn = columnIndex;
		std::cout << "tryWinnerMainDiagonalBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
		return true;
	}

	return false;
}

bool IGame::tryWinnerSecondaryDiagonalBySimbol(griglia & grid, simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerSecondaryDiagonalBySimbol" << std::endl;

	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int j=0;j<MATRIX_DIM;j++)
	{
		if(grid.getSymbol(MATRIX_DIM-j-1,j) == symb)
		{
			symbCount++;
		}
		else if(grid.getSymbol(MATRIX_DIM-j-1,j) == vuota)
		{
			isMissingCellFree = true;
			rowIndex = MATRIX_DIM-j-1;
			columnIndex = j;
		}
		else
			break;
	}

	if((symbCount == 2)&&(isMissingCellFree))
	{
		winnerRow = rowIndex;
		winnerColumn = columnIndex;
		std::cout << "tryWinnerSecondaryDiagonalBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
		return true;
	}

	return false;
}

bool IGame::tryNoLose(griglia & grid, simboli_t symb, int & row, int & column)
{
	std::cout << "tryNoLose" << std::endl;

	simboli_t enemySymb = symbolHandler::enemySymbol(symb);

	return tryToWin(grid, enemySymb, row, column);

}
