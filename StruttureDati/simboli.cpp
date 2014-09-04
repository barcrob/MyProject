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
