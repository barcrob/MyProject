#include "DialogMessage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


DialogMessage::DialogMessage(const QString & message):
QWidget()
{
	QVBoxLayout* layout = new QVBoxLayout();

	_message = new QLabel(message, this);
	_okButton = new QPushButton("&OK", this);

	layout->addWidget(_message);
	layout->addWidget(_okButton);
	layout->setContentsMargins(100, 20, 100, 20);
	setLayout(layout);

	connect(_okButton, SIGNAL(clicked()), this, SLOT(clickedSlot()));
}

DialogMessage::~DialogMessage()
{

}

void DialogMessage::clickedSlot()
{

}
