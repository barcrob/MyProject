#ifndef IGAME_H
#define IGAME_H

class IGame
{
	public:
		IGame();
		virtual ~IGame();

		virtual void play() = 0;
};

#endif // IGAME_H
