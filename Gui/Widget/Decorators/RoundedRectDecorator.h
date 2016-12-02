#ifndef ROUNDEDRECT_H
#define ROUNDEDRECT_H 

#include "DecoratorBase.h"


class RoundedRectDecorator: public DecoratorBase
{
	public:
		RoundedRectDecorator(ICellItem* cell,  const QRectF & coord, int width, const QColor & color);
		virtual ~RoundedRectDecorator();
		
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	private:
		int _width;
		QColor _color;
};
#endif //ROUNDEDRECT_H 
