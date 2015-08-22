/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include "MyDialog.h"

#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>

#include <iostream>

using namespace std;

MyDialog::MyDialog():
QWidget(),
_numPlayer(1)
{
	QGridLayout* layout = new QGridLayout();

	_combo = new QComboBox();
	_combo->addItem(QObject::tr("One player"));
	_combo->addItem(QObject::tr("Two player"));
	_okButton = new QPushButton("&OK", this);

	layout->addWidget(_combo);
	layout->addWidget(_okButton);
	layout->setContentsMargins(100, 20, 100, 20);
	setLayout(layout);

	connect(_combo, SIGNAL(activated(int)), this, SLOT(activatedSlot(int)));
	connect(_okButton, SIGNAL(clicked()), this, SLOT(clickedSlot()));
}

MyDialog::~MyDialog()
{
	cout << "~MyDialog" << endl;

 	disconnect(_combo, SIGNAL(activated(int)), this, SLOT(activatedSlot(int)));
	disconnect(_okButton, SIGNAL(clicked()), this, SLOT(clickedSlot()));
}

QSize MyDialog::minimumSizeHint()
{
	cout << "minimumSizeHint" << endl;
	return QSize(40, 80);
}

QSize MyDialog::sizeHint()
{
	cout << "sizeHint" << endl;
	return QSize(20000, 200);
}

void MyDialog::activatedSlot(int itemSelected)
{
	cout << "Selezionato item num = " << itemSelected+1 << endl;

	_numPlayer = itemSelected+1;

	QPixmap screenshot;

	screenshot = QPixmap::grabWidget(this);

	if(!screenshot.save("/home/roberto/projects/tris/build/screenshot", "png"))
	{
		cout << "ERROR in save file! " << endl;
	}
}

void MyDialog::clickedSlot()
{
	numPlayerSelected(_numPlayer);
	
	//deleteLater();
}