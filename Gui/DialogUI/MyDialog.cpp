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
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>


#include <iostream>

#define DIALOG_WITDH 200
#define DIALOG_HEIGHT 100

//NOTE trovare il modo di centralizzare queste informazioni
#define PLAYER1 "player1"
#define PLAYER2 "player2"

using namespace std;

MyDialog::MyDialog():
QWidget(),
_numPlayer(1)
{
	_layout = new QGridLayout();

	_title = new QLabel("Choose number of players");

	_combo = new QComboBox();
	_combo->addItem(QObject::tr("One player"));
	_combo->addItem(QObject::tr("Two player"));

	_layout->addWidget(_title);
	_layout->addWidget(_combo);

	_layout->setContentsMargins(100, 20, 100, 20);
	setLayout(_layout);
	
	setGeometry(0, QApplication::desktop()->screenGeometry().height()-DIALOG_HEIGHT, DIALOG_WITDH, DIALOG_HEIGHT);

	connect(_combo, SIGNAL(activated(int)), this, SLOT(activatedSlot(int)));
	
	
	setWindowTitle("Game Settings");
}

MyDialog::~MyDialog()
{
	cout << "~MyDialog" << endl;

 	disconnect(_combo, SIGNAL(activated(int)), this, SLOT(activatedSlot(int)));
	disconnect(_okButton, SIGNAL(clicked()), this, SLOT(OkClickedSlot()));
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
	
	_title->setText("Choose the symbol");
	_combo->hide();

	_groupBox = new QGroupBox();
	
	_symbolX = new QCheckBox("X", this);
	_symbolO = new QCheckBox("O", this);
	
	_symbolX->setAutoExclusive(true);
	_symbolO->setAutoExclusive(true);
	
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(_symbolX);
	vbox->addWidget(_symbolO);
	vbox->addStretch(1);
	
	_groupBox->setLayout(vbox);
	
	_layout->addWidget(_groupBox);

	_okButton = new QPushButton("&OK", this);
	_layout->addWidget(_okButton);
	_okButton->hide();

	connect(_okButton, SIGNAL(clicked()), this, SLOT(OkClickedSlot()));
	
	connect(_symbolO, SIGNAL(clicked()), this, SLOT(groupClickedSlot()));
	connect(_symbolX, SIGNAL(clicked()), this, SLOT(groupClickedSlot()));
}

void MyDialog::OkClickedSlot()
{
	numPlayerSelected(_numPlayer);
	
	if(_symbolX->isChecked())
	{
		symbolChoiceSignal(PLAYER1, QString("X"));
	}
	else if(_symbolO->isChecked())
	{
		symbolChoiceSignal(PLAYER1, QString("O"));
	}
}

void MyDialog::groupClickedSlot()
{
	_okButton->show();
}
