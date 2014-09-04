#include "griglia.h"

#include <iostream>
#include <stdlib.h>

griglia::griglia()
{
	clear();
}

void griglia::clear()
{
	for(int i=0;i<MATRIX_DIM;i++)
	{
		for(int j=0;j<MATRIX_DIM;j++)
			celle[i][j].setSimbolo(vuota);;
	}
}

void griglia::print(){
	
	std::cout << std::endl;

	for(int i=0;i<MATRIX_DIM;i++)
	{
		std::cout << " -------------" << std::endl;

		for(int j=0;j<MATRIX_DIM;j++)
		{
			std::cout << " | ";
			celle[i][j].stampaSimbolo();
		}

		std::cout << " | " << std::endl;
	}

	std::cout << " -------------" << std::endl;
}

bool griglia::checkRange(int row, int col)
{
	return (row>=0 && row<MATRIX_DIM) && (col>=0 && col<MATRIX_DIM);
}

bool griglia::setSymbol(int row, int col, simboli_t simb)
{
	if(checkRange(row, col))
	{
		return celle[row][col].setSimbolo(simb);
	}
	else
	{
		std::cout << std::endl << "setSymbol posizione non corretta" << std::endl;
		exit(EXIT_FAILURE);
		//return false;
	}
}

simboli_t griglia::getSymbol(int row, int col)
{
	if(checkRange(row, col))
	{
		return celle[row][col].getSimbolo();
	}
	else
	{
		std::cout << std::endl << "getSymbol posizione non corretta" << std::endl;
		exit(EXIT_FAILURE);
		//return vuota;
	}
}

bool griglia::isFilled()
{
	for(int i=0;i<MATRIX_DIM;i++)
	{
		for(int j=0;j<MATRIX_DIM;j++)
		{
			if(celle[i][j].isEmpty())
				return false;
		}
	}

	return true;
}

bool griglia::isAnyRowTris()
{
	for(int i=0;i<MATRIX_DIM;i++)
	{
		simboli_t simbolo = getSymbol(i,0);

		if(simbolo == vuota)
		{
			continue;
		}

		if((getSymbol(i,1) != simbolo)||(getSymbol(i,2) != simbolo))
		{
			continue;
		}

		return true;
	}

	return false;
}

bool griglia::isAnyColumnTris()
{
	for(int j=0;j<MATRIX_DIM;j++)
	{
		simboli_t simbolo = getSymbol(0,j);

		if(simbolo == vuota)
		{
			continue;
		}

		if((getSymbol(1,j) != simbolo)||(getSymbol(2,j) != simbolo))
		{
			continue;
		}

		return true;
	}

	return false;
}

bool griglia::isAnyDiagonalTris()
{
	simboli_t simboloCentrale = celle[1][1].getSimbolo();

	if(simboloCentrale == vuota)
		return false;

	if((getSymbol(0,0) == simboloCentrale) && (getSymbol(2,2) == simboloCentrale))
	{
		//std::cout << std::endl << "Diagonale sinistra" << std::endl;
		return true;
	}

	if((getSymbol(0,2) == simboloCentrale) && (getSymbol(2,0) == simboloCentrale))
	{
		//std::cout << std::endl << "Diagonale destra" << std::endl;
		return true;
	}

	return false;
}

bool griglia::isAnyTris()
{
	return isAnyRowTris() || isAnyColumnTris() || isAnyDiagonalTris();
}


/*
 * Se trovo una posizione che mi permette di vincere componendo una riga restituisco le coordinate vincenti
 * altrimenti restituisco le ultime coordinate vuote trovate. Per ora non è una tattica intelligente. poi verrà migliorata
 */
bool griglia::tryWinnerRowBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
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
			if(getSymbol(i,j) == symb)
			{
				symbCount++;
			}
			else if(getSymbol(i,j) == vuota)
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


bool griglia::tryWinnerColumnBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
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
			if(celle[i][j].getSimbolo() == symb)
			{
				symbCount++;
			}
			else if(celle[i][j].getSimbolo() == vuota)
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

bool griglia::tryWinnerMainDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerMainDiagonalBySimbol" << std::endl;
	
	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int i=0;i<MATRIX_DIM;i++)
	{

		if(celle[i][i].getSimbolo() == symb)
		{
			symbCount++;
		}
		else if(celle[i][i].getSimbolo() == vuota)
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

bool griglia::tryWinnerSecondaryDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerSecondaryDiagonalBySimbol" << std::endl;
	
	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int j=0;j<MATRIX_DIM;j++)
	{
		if(celle[MATRIX_DIM-j-1][j].getSimbolo() == symb)
		{
			symbCount++;
		}
		else if(celle[MATRIX_DIM-j-1][j].getSimbolo() == vuota)
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

bool griglia::tryNoLose(simboli_t symb, int & row, int & column)
{
	std::cout << "tryNoLose" << std::endl;
	
	simboli_t enemySymb = symbolHandler::enemySymbol(symb);

	return tryToWin(enemySymb, row, column);

}

bool griglia::tryToWin(simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryToWin" << std::endl;

	if(tryWinnerRowBySimbol(symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente su riga: " << winnerRow << std::endl;
		return true;
	}

	if(tryWinnerColumnBySimbol(symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente su colonna: " << winnerColumn << std::endl;
		return true;
	}

	if(tryWinnerMainDiagonalBySimbol(symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	if(tryWinnerSecondaryDiagonalBySimbol(symb, winnerRow, winnerColumn))
	{
		std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	std::cout << "tryToWin nessuna mossa vincente trovata" << std::endl;

	return false;
}

bool griglia::firstEmptyCell(int& row, int& col)
{
	std::cout << "firstEmptyCell" << std::endl;
	
	for(int i=0;i<MATRIX_DIM;i++)
	{
		for(int j=0;j<MATRIX_DIM;j++)
		{
			if(celle[i][j].isEmpty())
			{
				row = i;
				col = j;
				std::cout << "firstEmptyCell row = " << row << "col = " << col << std::endl;

				return true;
			}
		}
	}

	return false;
}
