#ifndef IGAME_H
#define IGAME_H

#include "griglia.h"

typedef enum
{
	rowType,
	columnType
}coordinateType_t;

class IGame
{
	public:
		IGame();
		virtual ~IGame();

		virtual void play() = 0;

	protected:
		griglia _grid;
};

#endif // IGAME_H
