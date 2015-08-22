#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

#include <QGraphicsView>

class IGameView: public QGraphicsView
{
	Q_OBJECT

	public:
		IGameView();
		~IGameView();

		virtual void setSymbol(int row, int col, const QString symbol) = 0;
		virtual const QString getSymbol(int row, int col) const = 0;

	Q_SIGNALS:
		void cellSelected(int, int);
};

#endif // IGAMEVIEW_H
