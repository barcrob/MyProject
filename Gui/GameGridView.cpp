#include "GameGridView.h"

#include "CellGraphicItem.h"
#include "ICellDecorator.h"
#include <RoundedRectDecorator.h>

#include <QKeyEvent>

#include <iostream>

using namespace std;

#define MARGIN 10

GameGridView::GameGridView(const QRectF & dim):
IGameView()
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			float cellWidth = (dim.width()-5*MARGIN)/3;
			float cellHeight = (dim.height()-5*MARGIN)/3;
			QRectF cellPosition(x() + MARGIN + cellWidth/2 + (cellWidth+MARGIN)*col, y() + MARGIN + cellHeight/2 + (cellHeight+MARGIN)*row , cellWidth,  cellHeight);
			//ICellItem* cellElement = new CellGraphicItem(cellPosition, row, col, QString(" "));
			//_grid[row][col] =  new RoundedRectDecorator(cellElement);
			_grid[row][col] =  new CellGraphicItem(cellPosition, row, col, QString(" "));
			scene->addItem(_grid[row][col]);

			connect(_grid[row][col], SIGNAL(cellSelected(int, int)), this, SLOT(cellSelectedSlot(int, int)));
		}
	}
	setScene(scene);
}

GameGridView::~GameGridView()
{
	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			disconnect(_grid[row][col], SIGNAL(cellSelected(int, int)), this, SLOT(cellSelectedSlot(int, int)));
		}
	}
}

void GameGridView::cellSelectedSlot(int row, int col)
{
	//Temporaneo, solo per aver un riscontro grafico della selezione
	_grid[row][col]->setSymbol("X");

	cellSelected(row, col);
}

const QString GameGridView::getSymbol(int row, int col) const
{
	return _grid[row][col]->getSymbol();
}

void GameGridView::setSymbol(int row, int col, const QString symbol)
{
		_grid[row][col]->setSymbol(symbol);
}
