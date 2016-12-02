#include "RectDecorator.h"

#include <QString>
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>


RectDecorator::RectDecorator(ICellItem* cell,  const QRectF & coord, int width, const QColor & color):
DecoratorBase(cell, coord),
_width(width),
_color(color)
{
}

RectDecorator::~RectDecorator()
{
}


void RectDecorator::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	int penWitdh = abs(_width);
	pen.setWidth(penWitdh);
	pen.setBrush(_color);

	qreal penWitdhHalf = _width/2;
	painter->setPen(pen);
	painter->drawRect(_cell->boundingRect().adjusted(penWitdhHalf, penWitdhHalf, -penWitdhHalf, -penWitdhHalf));

	DecoratorBase::paint(painter, option, widget);
}






