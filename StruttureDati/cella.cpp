#include "cella.h"

#include <iostream>

void cella::stampaSimbolo()
{
		switch(_simbolo)
		{
			case cerchio:
				std::cout << 'O';
			break;

			case croce:
				std::cout << 'X';
			break;

			case vuota:
				std::cout << ' ';
			break;
		}
}

bool cella::setSimbolo(simboli_t simb)
{
	if(simb<vuota || simb >croce)
	{
		std::cout << "ATTENZIONE simbolo non valido!!" << std::endl;
		return false;
	}

	if(_simbolo != vuota)
	{
		std::cout << "ATTENZIONE posizione già occupata!!" << std::endl;
		return false;
	}

	_simbolo = simb;
	return true;
}

