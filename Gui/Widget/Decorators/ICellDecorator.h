#ifndef IDECORATOR_H
#define IDECORATOR_H

#include "ICellItem.h"


#include <QRect>

class QWidget;
class QStyleOptionGraphicsItem;
class QPainter;

class ICellDecorator: public ICellItem
{
	public:
		ICellDecorator(ICellItem* cell):
		ICellItem(),
		_cell(cell){};
		virtual ~ICellDecorator(){};

		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0){_cell->paint(painter, option, widget);};
		
	protected:
		ICellItem* _cell;
};

#endif //IDECORATOR_H

