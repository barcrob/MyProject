#ifndef CELLGRAPHICITEM_H
#define CELLGRAPHICITEM_H

#include "ICellItem.h"




class QStyleOptionGraphicsItem;
class QGraphicsSceneMouseEvent;
class QGraphicsSimpleTextItem;
class QPainter;


class CellGraphicItem: public QObject,  public QGraphicsRectItem
{
	Q_OBJECT
	
	public:
		CellGraphicItem(const QRectF & coord, int row, int col, const QString & symbol);
		~CellGraphicItem();

		void setSymbol(const QString symbol);
		const QString getSymbol() const;
		
		//void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	  //QRectF boundingRect() const;

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

	Q_SIGNALS:
		void cellSelected(int row, int col);

	private:
		QGraphicsSimpleTextItem* _symbol;
		int _row;
		int _col;
};

#endif // CELLGRAPHICITEM_H
