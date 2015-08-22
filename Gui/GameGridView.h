#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "IGameView.h"

class ICellItem;
class CellGraphicItem;


class GameGridView: public IGameView
{
	Q_OBJECT

	public:
		GameGridView(const QRectF & dim);
		~GameGridView();

		virtual void setSymbol(int row, int col, const QString symbol);
		virtual const QString getSymbol(int row, int col) const;
		
	private Q_SLOTS:
		void cellSelectedSlot(int, int);

	private:
		CellGraphicItem* _grid[3][3];
};

#endif // GAMEGRID_H
