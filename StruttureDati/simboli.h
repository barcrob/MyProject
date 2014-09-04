#ifndef SIMBOLI_H
#define SIMBOLI_H

typedef enum
{
	vuota,
	cerchio,
	croce,
}simboli_t;

class symbolHandler
{
public:
	static simboli_t enemySymbol(simboli_t symb);
};

#endif