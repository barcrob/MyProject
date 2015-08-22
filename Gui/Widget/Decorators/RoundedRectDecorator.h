#ifndef ROUNDEDRECT_H
#define ROUNDEDRECT_H 

#include "ICellDecorator.h"


class RoundedRectDecorator: public ICellDecorator
{
	public:
		RoundedRectDecorator(ICellItem* cell);
		virtual ~RoundedRectDecorator(){};
		
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	  QRectF boundingRect() const;
		void setSymbol(const QString symbol);
		const QString getSymbol() const;
};
#endif //ROUNDEDRECT_H 
