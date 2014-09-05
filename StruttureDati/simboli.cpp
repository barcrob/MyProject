#include "simboli.h"



simboli_t symbolHandler::enemySymbol(simboli_t symb)
{
	simboli_t enemySymb;

	switch(symb)
	{
		case cerchio:
			enemySymb = croce;
			break;

		case croce:
			enemySymb = cerchio;
			break;

		default:
			enemySymb = vuota;
	}

	return enemySymb;
}

char symbolHandler::toChar(simboli_t symb)
{
	char s;
	
	switch(symb)
	{
		case cerchio:
			s = 'O';
			break;

		case croce:
			s = 'X';
			break;

		default:
			s = ' ';
	}

	return s;
}
