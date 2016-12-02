#ifndef ICELLITEM_H
#define ICELLITEM_H

#include <QGraphicsRectItem>

class QRectF;
class QGraphicsSceneMouseEvent;

class ICellItem: public QObject, public QGraphicsRectItem
{
	Q_OBJECT

	public:
		ICellItem(const QRectF & coord);
		virtual ~ICellItem();

		virtual void setSymbol(const QString symbol) = 0;
		virtual const QString getSymbol() const = 0;
		virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
		
		virtual QGraphicsSimpleTextItem* getSymbolItem() const = 0;

	Q_SIGNALS:
		void cellSelectedSignal(int row, int col);

	private:
		static int _count;
};
#endif //ICELLITEM_H