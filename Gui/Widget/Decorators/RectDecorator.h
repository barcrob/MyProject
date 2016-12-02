#ifndef RECTDECORATOR_H
#define RECTDECORATOR_H

#include "DecoratorBase.h"


class RectDecorator: public DecoratorBase
{
	public:
		RectDecorator(ICellItem* cell,  const QRectF & coord, int width, const QColor & color);
		virtual ~RectDecorator();
		
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	private:
		int _width;
		QColor _color;
};
#endif //RECTDECORATOR_H 