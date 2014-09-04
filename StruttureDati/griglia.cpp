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
