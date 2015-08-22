#include "CellGraphicItem.h"

#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>

using namespace std;

CellGraphicItem::CellGraphicItem(const QRectF & coord, int row, int col, const QString & symbol):
QObject(),
QGraphicsRectItem(coord),
_symbol(NULL),
_row(row),
_col(col)
{
	_symbol = new QGraphicsSimpleTextItem(symbol, this);

	float x = coord.x()+(boundingRect().width() -_symbol->boundingRect().width())/2;
	float y = coord.y()+(boundingRect().height()-_symbol->boundingRect().height())/2;
	
	_symbol->setPos(x,y);

	setBrush(QBrush(QColor(122,122,122,128)));
}

CellGraphicItem::~CellGraphicItem()
{
}

void CellGraphicItem::setSymbol(const QString symbol)
{
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
				cellSelected(_row, _col);
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
// // 	QPen pen;
// // 	pen.setWidth(2);
// // 	painter->setPen(pen);
// // 	painter->drawRoundedRect(boundingRect(), 50.0, 50.0, Qt::RelativeSize);
// 	QGraphicsRectItem::paint(painter, option, widget);
// }

// QRectF CellGraphicItem::boundingRect() const
// {
// 	return QGraphicsRectItem::boundingRect();
// }
