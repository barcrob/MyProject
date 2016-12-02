#include "ICellItem.h"

#include <iostream>

int ICellItem::_count = 0;

using namespace std;

ICellItem::ICellItem(const QRectF & coord):
QGraphicsRectItem(coord)
{
	_count++;
	//cout << "create ICellItem count = " << _count << endl;
}

ICellItem::~ICellItem()
{
	_count--;
	//cout << "destroy ICellItem count = " << _count << endl;
}
