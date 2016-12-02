#ifndef CELLGRAPHICITEM_H
#define CELLGRAPHICITEM_H

#include "ICellItem.h"




class QStyleOptionGraphicsItem;
class QGraphicsSceneMouseEvent;
class QGraphicsSimpleTextItem;
class QPainter;


class CellGraphicItem: public ICellItem
{
	Q_OBJECT
	
	public:
		CellGraphicItem(const QRectF & coord, int row, int col, const QString & symbol);
		~CellGraphicItem();

		void setSymbol(const QString symbol);
		const QString getSymbol() const;
		
		QGraphicsSimpleTextItem* getSymbolItem() const {return _symbol;};
		
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *event);


	private:
		QGraphicsSimpleTextItem* _symbol;
		int _row;
		int _col;
		static int _count;
};

#endif // CELLGRAPHICITEM_H
