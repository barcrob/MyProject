#ifndef ICELLITEM_H
#define ICELLITEM_H

#include <QRect>
#include <QRectF>
#include <QGraphicsRectItem>

class QWidget;
class QStyleOptionGraphicsItem;
class QPainter;
class QString;

class ICellItem: public QObject,  public QGraphicsRectItem
{
	Q_OBJECT

	public:
		ICellItem();
		virtual ~ICellItem();
		
		virtual void setSymbol(const QString symbol) = 0;
		virtual const QString getSymbol() const = 0;
		
		virtual QRectF boundingRect() const = 0;
		
		//virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;
		
	Q_SIGNALS:
		void cellSelected(int row, int col);
};
#endif //ICELLITEM_H