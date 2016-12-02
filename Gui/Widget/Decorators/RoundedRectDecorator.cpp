#include "RoundedRectDecorator.h"

#include <QString>
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>


RoundedRectDecorator::RoundedRectDecorator(ICellItem* cell,  const QRectF & coord, int width, const QColor & color):
DecoratorBase(cell, coord),
_width(width),
_color(color)
{
}

RoundedRectDecorator::~RoundedRectDecorator()
{
}


void RoundedRectDecorator::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	int penWitdh = abs(_width);
	pen.setWidth(penWitdh);
	pen.setBrush(_color);

	qreal penWitdhHalf = _width/2;
	painter->setPen(pen);
	painter->drawRoundedRect(_cell->boundingRect().adjusted(penWitdhHalf, penWitdhHalf, -penWitdhHalf, -penWitdhHalf), 50.0, 50.0, Qt::RelativeSize);

	DecoratorBase::paint(painter, option, widget);
}






