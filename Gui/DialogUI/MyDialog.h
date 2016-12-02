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

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QtGui/QWidget>

class QGroupBox;
class QButtonGroup;
class QGridLayout;
class QCheckBox;
class QLabel;
class QComboBox;

class QPushButton;

class MyDialog : public QWidget
{
	Q_OBJECT
	
public:
	MyDialog();
	virtual ~MyDialog();

	virtual QSize minimumSizeHint();
	virtual QSize sizeHint();


 private Q_SLOTS:
		void activatedSlot(int);
		void OkClickedSlot();
		void groupClickedSlot();

Q_SIGNALS:
	void numPlayerSelected(int numPlayer);
	void symbolChoiceSignal(const QString & playerId, const QString & symbol);

private:
	QGridLayout* _layout;
	QLabel* _title;
	QComboBox* _combo;
	QPushButton* _okButton;
	QGroupBox* _groupBox;
	QCheckBox* _symbolX;
	QCheckBox* _symbolO;
	int _numPlayer;
};

#endif // MYDIALOG_H
