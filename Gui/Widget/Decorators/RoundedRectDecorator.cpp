#include "RoundedRectDecorator.h"

#include <QString>
#include <qpen.h>
#include <QPainter>
#include <qstyleoption.h>

#include <iostream>


RoundedRectDecorator::RoundedRectDecorator(ICellItem* cell):
ICellDecorator(cell)
{

}

void RoundedRectDecorator::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	std::cout << "RoundedRectDecorator::paint" << std::endl;
	
	QPen pen;
	pen.setWidth(3);
	painter->setPen(pen);
	painter->drawRoundedRect(_cell->boundingRect(), 50.0, 50.0, Qt::RelativeSize);
	ICellDecorator::paint(painter, option, widget);
}

const QString RoundedRectDecorator::getSymbol() const
{
	if(_cell)
		_cell->getSymbol();
}

void RoundedRectDecorator::setSymbol(const QString symbol)
{
	if(_cell)
		_cell->setSymbol(symbol);
}

QRectF RoundedRectDecorator::boundingRect() const
{
	QRectF rect;
	
	if(_cell)
		rect = _cell->boundingRect();
	
	return rect;
	
}







