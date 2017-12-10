#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QLabel>


class TimeStamp : public QLabel
{
	Q_OBJECT

public:
	TimeStamp(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *event);
};

#endif // TIMESTAMP_H
