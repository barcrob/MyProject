#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QWidget>

class QPushButton;
class QLabel;

class DialogMessage: public QWidget
{
	Q_OBJECT

	public:
		DialogMessage(const QString & message);
		~DialogMessage();

	private Q_SLOTS:
		void clickedSlot();

private:
	QLabel* _message;
	QPushButton* _okButton;
};

#endif // DIALOGMESSAGE_H
