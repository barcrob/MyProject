#include "GameBase.h"
#include <readUtility.h>

#include <iostream>

GameBase::GameBase(GameManager & manager):
IGame(manager),
_gameView(NULL)
{

}

GameBase::~GameBase()
{

}

bool GameBase::tryToWin(simboli_t symb, int& winnerRow, int& winnerColumn)
{
	//std::cout << "tryToWin" << std::endl;

	if(tryWinnerRowBySimbol(symb, winnerRow, winnerColumn))
	{
		//std::cout << "tryToWin trovata mossa vincente su riga: " << winnerRow << std::endl;
		return true;
	}

	if(tryWinnerColumnBySimbol(symb, winnerRow, winnerColumn))
	{
		//std::cout << "tryToWin trovata mossa vincente su colonna: " << winnerColumn << std::endl;
		return true;
	}

	if(tryWinnerMainDiagonalBySimbol(symb, winnerRow, winnerColumn))
	{
		//std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	if(tryWinnerSecondaryDiagonalBySimbol(symb, winnerRow, winnerColumn))
	{
		//std::cout << "tryToWin trovata mossa vincente sulla diagonale principale" << std::endl;
		return true;
	}

	//std::cout << "tryToWin nessuna mossa vincente trovata" << std::endl;

	return false;
}


/*
 * Se trovo una posizione che mi permette di vincere componendo una riga restituisco le coordinate vincenti
 * altrimenti restituisco le ultime coordinate vuote trovate. Per ora non è una tattica intelligente. poi verrà migliorata
 */
bool GameBase::tryWinnerRowBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
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
			if(_grid.getSymbol(i,j)== symb)
			{
				symbCount++;
			}
			else if(_grid.getSymbol(i,j) == vuota)
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
			//std::cout << "tryWinnerRowBySimbol TROVATA UNA MOSSA VINCENTE NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
			return true;
		}
	}

	return false;
}

bool GameBase::tryWinnerColumnBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
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
			if(_grid.getSymbol(i,j) == symb)
			{
				symbCount++;
			}
			else if(_grid.getSymbol(i,j) == vuota)
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
			//std::cout << "tryWinnerColumnBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
			return true;
		}
	}

	return false;
}

bool GameBase::tryWinnerMainDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
{
	//std::cout << "tryWinnerMainDiagonalBySimbol" << std::endl;

	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int i=0;i<MATRIX_DIM;i++)
	{

		if(_grid.getSymbol(i,i) == symb)
		{
			symbCount++;
		}
		else if(_grid.getSymbol(i,i) == vuota)
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
		//std::cout << "tryWinnerMainDiagonalBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
		return true;
	}

	return false;
}

bool GameBase::tryWinnerSecondaryDiagonalBySimbol(simboli_t symb, int & winnerRow, int & winnerColumn)
{
	std::cout << "tryWinnerSecondaryDiagonalBySimbol" << std::endl;

	int symbCount = 0;
	bool isMissingCellFree = false;
	int rowIndex = 0;
	int columnIndex = 0;

	for(int j=0;j<MATRIX_DIM;j++)
	{
		if(_grid.getSymbol(MATRIX_DIM-j-1,j) == symb)
		{
			symbCount++;
		}
		else if(_grid.getSymbol(MATRIX_DIM-j-1,j) == vuota)
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
		//std::cout << "tryWinnerSecondaryDiagonalBySimbol MOSSA VINCENTE CON SIMBOLO NELLA CELLA (" << winnerRow+1 << "," << winnerColumn+1 << ")" << std::endl;
		return true;
	}

	return false;
}

bool GameBase::tryNoLose(simboli_t symb, int & row, int & column)
{
	//std::cout << "tryNoLose" << std::endl;

	simboli_t enemySymb = symbolHandler::enemySymbol(symb);

	return tryToWin(enemySymb, row, column);

}

bool GameBase::leggiCoordinata(int & coord, coordinateType_t type)
{
		bool validValue = false;

		while(!validValue)
		{
			std::string coordinata = (type == rowType)? "riga" : "colonna" ;
			std::cout << "Inserire il numero di " << coordinata << " :" << std::endl;
			std::cout << "1)" << std::endl;
			std::cout << "2)" << std::endl;
			std::cout << "3)" << std::endl;
			std::cout << "4) Per uscire dalla partita" << std::endl;

			if(readUtility::safeReadInt(coord))
			{
				if(coord == 4)
				{
					std::cout << "Primo ramo if" << std::endl;
					return false;
				}
				else if(coord>0 && coord<=MATRIX_DIM)
				{
					std::cout << "Secondo ramo if" << std::endl;
					validValue = true;
					return true;
				}
				else
				{
					std::cout << "ramo else" << std::endl;
					std::cout << "Valore non valido, riprovare" << std::endl;
				}
			}
			else
			{
				std::cout << "ramo else" << std::endl;
				std::cout << "Valore non valido, riprovare" << std::endl;
			}
		}
}

bool GameBase::inserisciMossa(simboli_t simbolo)
{
	bool mossaValida = false;

	while(!mossaValida)
	{
		std::cout << "Inserisci le coordinate della cella:" << std::endl << std::endl;

		int row = 0;

		if(!leggiCoordinata(row, rowType))
			return false;

		int col = 0;

		if(!leggiCoordinata(col, columnType))
			return false;

		mossaValida = _grid.setSymbol(row-1, col-1, simbolo);

		if(!mossaValida) _grid.print();
	}

	return true;
}