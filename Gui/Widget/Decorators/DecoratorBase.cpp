#include "DecoratorBase.h"

#include <QStyleOptionGraphicsItem>
#include <QPainter>

DecoratorBase::DecoratorBase(ICellItem* cell, const QRectF & coord): 
ICellItem(coord),
_cell(cell)
{
	connect(cell, SIGNAL(cellSelectedSignal(int, int)), this, SIGNAL(cellSelectedSignal(int, int)));
}

DecoratorBase::~DecoratorBase()
{
	if(_cell)
		disconnect(_cell, SIGNAL(cellSelectedSignal(int, int)), this, SIGNAL(cellSelectedSignal(int, int)));
	
	delete _cell;
}

void DecoratorBase::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if(_cell)
	_cell->paint(painter, option, widget);    
}

const QString DecoratorBase::getSymbol() const
{
	if(_cell)
	_cell->getSymbol();
}

void DecoratorBase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if(_cell)
	_cell->mousePressEvent(event);
}

void DecoratorBase::setSymbol(const QString symbol)
{
	if(_cell)
	_cell->setSymbol(symbol);
}

QGraphicsSimpleTextItem* DecoratorBase::getSymbolItem() const
{
	if(_cell)
		_cell->getSymbolItem();
}
