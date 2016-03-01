#ifndef QTDEMO_64_H
#define QTDEMO_64_H

#include <QtGui/QMainWindow>
#include "ui_qtdemo_64.h"

class Qtdemo_64 : public QMainWindow
{
	Q_OBJECT

public:
	Qtdemo_64(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Qtdemo_64();
	void ConnectGui();
	void DisconnectGui();
	void UpdateButtons();

private:
	Ui::Qtdemo_64Class ui;

private slots:
	void on_DigitalIoBtn_clicked();
	void on_AnalogIoBtn_clicked();
	void on_WriteEepromBtn_clicked();
	void on_DisableGraphChk_stateChanged(int);
	void on_DeactivateBtn_clicked();
	void on_ReadEepromBtn_clicked();
	void on_ActivateBtn_clicked();
	void on_UpdateListBtn_clicked();
	void on_StopMeasBtn_clicked();
	void on_StartMeasBtn_clicked();
	void on_ShowEepromBtn_clicked();
	void on_OpenCommBtn_clicked();
	void on_CloseCommBtn_clicked();
	void on_SpectrometerList_clicked();

public slots:
	void ReceiveDataIsHere(int WParam, int LParam);
	// avoid a name starting with "on_" here, otherwise you will get a
	// warning, as there is no defined signal, just an emit in "application.cpp"

};

#endif // QTDEMO_64_H
