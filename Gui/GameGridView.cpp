#include "GameGridView.h"

#include "CellGraphicItem.h"
#include "RoundedRectDecorator.h"
#include "RectDecorator.h"
#include <GameManager.h>
#include <IGame.h>

#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

using namespace std;


#define WITDH 300
#define HEIGHT 300
#define MARGIN 10

GameGridView::GameGridView(GameManager & manager):
IGameView(),
_manager(manager)
{
	QRectF dim(0,0,WITDH, HEIGHT );
	
	QGraphicsScene *scene = new QGraphicsScene(this);
	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			float cellWidth = (dim.width()-5*MARGIN)/3;
			float cellHeight = (dim.height()-5*MARGIN)/3;
			QRectF cellPosition(x() + MARGIN + cellWidth/2 + (cellWidth+MARGIN)*col, y() + MARGIN + cellHeight/2 + (cellHeight+MARGIN)*row , cellWidth,  cellHeight);
			ICellItem* cellElement = new CellGraphicItem(cellPosition, row, col, QString(" "));
			
			_grid[row][col] = cellElement;

			scene->addItem(cellElement->getSymbolItem());
			scene->addItem(_grid[row][col]);

			connect(_grid[row][col], SIGNAL(cellSelectedSignal(int, int)), this, SLOT(cellSelectedSlot(int, int)));
		}
	}
	setScene(scene);
	
	setGeometry(0, QApplication::desktop()->screenGeometry().height()-WITDH, WITDH, HEIGHT);
}

GameGridView::~GameGridView()
{
	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			disconnect(_grid[row][col], SIGNAL(cellSelectedSignal(int, int)), this, SLOT(cellSelectedSlot(int, int)));
		}
	}
}

void GameGridView::cellSelectedSlot(int row, int col)
{
	cout << "GameGridView::cellSelectedSlot (" << row << "," << col << ")" << endl;

 	disconnect(_grid[row][col], SIGNAL(cellSelectedSignal(int, int)), this, SLOT(cellSelectedSlot(int, int)));

	scene()->removeItem(_grid[row][col]);
	_grid[row][col] = new RectDecorator(_grid[row][col], _grid[row][col]->boundingRect(), 3, QColor("red"));
	scene()->addItem(_grid[row][col]);

	cellSelectedSignal(row, col);
	setInteractive(false);
}

const QString GameGridView::getSymbol(int row, int col) const
{
	return _grid[row][col]->getSymbol();
}

void GameGridView::setSymbol(int row, int col, const QString symbol)
{
		_grid[row][col]->setSymbol(symbol);
}

void GameGridView::connectData()
{
	cout << "GameGridView::connectData" << endl;
	
	connect(&_manager.getGame(), SIGNAL(symbolSelectedSignal(int, int, const QString &)), this, SLOT(symbolSelectedSlot(int, int, const QString &)));
}

void GameGridView::disconnectData()
{
	cout << "GameGridView::disconnectData" << endl;
	
	disconnect(&_manager.getGame(), SIGNAL(symbolSelectedSignal(int, int, const QString &)), this, SLOT(symbolSelectedSlot(int, int, const QString &)));
}

void GameGridView::symbolSelectedSlot(int row, int col, const QString & symbol)
{
	cout << "GameGridView::symbolSelectedSlot" << endl;
	
	setSymbol(row, col, symbol);
	setInteractive(true);
}

