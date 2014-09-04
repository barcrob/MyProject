#ifndef CELLA_H
#define CELLA_H

#include "simboli.h"

class cella
{
public:
	cella():_simbolo(vuota){};

	bool setSimbolo(simboli_t simb);

	simboli_t getSimbolo(){return _simbolo;};

	void stampaSimbolo();

	bool isEmpty(){return _simbolo == vuota;};

private:
	simboli_t _simbolo;
};

#endif // CELLA_H
