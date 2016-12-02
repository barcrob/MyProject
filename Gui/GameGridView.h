#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "IGameView.h"

class GameManager;
class ICellItem;


class GameGridView: public IGameView
{
	Q_OBJECT

	public:
		GameGridView(GameManager & manager);
		~GameGridView();

		virtual void setSymbol(int row, int col, const QString symbol);
		virtual const QString getSymbol(int row, int col) const;
		
		void connectData();
		void disconnectData();
		
	private Q_SLOTS:
		void cellSelectedSlot(int, int);
		void symbolSelectedSlot(int, int, const QString &);

	private:
		ICellItem* _grid[3][3];
		GameManager & _manager;
};

#endif // GAMEGRID_H
