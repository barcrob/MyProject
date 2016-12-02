#ifndef IDECORATOR_H
#define IDECORATOR_H

#include "ICellItem.h"

class QPainter;
class QWidget;
class QStyleOptionGraphicsItem;


class DecoratorBase: public ICellItem
{
	public:
		DecoratorBase(ICellItem* cell, const QRectF & coord);
		virtual ~DecoratorBase();

		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

		void setSymbol(const QString symbol);
		const QString getSymbol() const;
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

		QGraphicsSimpleTextItem* getSymbolItem() const;

	protected:
		ICellItem* _cell;
};

#endif //IDECORATOR_H

