#ifndef QTDEMO_H
#define QTDEMO_H

#include <QDialog>

class QPushButton;
class QLabel;
class QLineEdit;
class RenderArea;
class TimeStamp;
class Plot;

class Qtdemo : public QDialog
{
	Q_OBJECT  

public:
	Qtdemo(QWidget *parent = 0);
	~Qtdemo();
  
private:
	QPushButton *OpenCommBtn;
    QPushButton *CloseCommBtn;
    QPushButton *StartMeasBtn;
    QPushButton *StopMeasBtn;
	QLineEdit *edtIntTime;
	QLineEdit *edtNumAvg;
	QLineEdit *edtNumMeas;
 	QLabel *TimeStampLabel;
	QLabel *IntTimeLabel;
	QLabel *NumAvgLabel;
	QLabel *NumMeasLabel;
	RenderArea *renderArea;
	TimeStamp *timeStamp;
	Plot *plot;

private slots:
	void on_StopMeasBtn_clicked();
	void on_StartMeasBtn_clicked();
	void on_CloseCommBtn_clicked();
	void on_OpenCommBtn_clicked();

public slots:
	void on_DataIsHere(int newValue);

};

#endif // QTDEMO_H
