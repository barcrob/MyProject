#include "CellGraphicItem.h"

#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>

int CellGraphicItem::_count = 0;

using namespace std;

CellGraphicItem::CellGraphicItem(const QRectF & coord, int row, int col, const QString & symbol):
ICellItem(coord),
_symbol(NULL),
_row(row),
_col(col)
{
	_symbol = new QGraphicsSimpleTextItem(symbol, this);

	float x = coord.x()+(boundingRect().width() -_symbol->boundingRect().width())/2;
	float y = coord.y()+(boundingRect().height()-_symbol->boundingRect().height())/2;

	_symbol->setPos(x,y);

	setBrush(QBrush(QColor(80,80,80,125)));

	_count++;
	cout << "create CellGraphicItem count = " << _count << endl;
}

CellGraphicItem::~CellGraphicItem()
{
	_count--;
	cout << "destroy CellGraphicItem count = " << _count << endl;
}

void CellGraphicItem::setSymbol(const QString symbol)
{
	cout << "CellGraphicItem::setSymbol " << symbol.toStdString() << endl;

	_symbol->setText(symbol);
}

const QString CellGraphicItem::getSymbol() const
{
	return _symbol->text();
}

void CellGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     if (event->button() == Qt::LeftButton) {
         // handle left mouse button here
				cout << "CellGraphicItem::Il giocatore ha scelto la cella (" << _row << "," << _col << ")" << endl;
				cellSelectedSignal(_row, _col);
				setAcceptedMouseButtons(0);
     } else {
         // pass on other buttons to base class
         QGraphicsRectItem::mousePressEvent(event);
     }
}

// void CellGraphicItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
// {
// 	std::cout << "CellGraphicItem::paint" << std::endl;
// 
// 	_symbol->paint(painter, option, widget);
// 	QGraphicsRectItem::paint(painter, option, widget);
// }

// QRectF CellGraphicItem::boundingRect() const
// {
// 	return QGraphicsRectItem::boundingRect();
// }
