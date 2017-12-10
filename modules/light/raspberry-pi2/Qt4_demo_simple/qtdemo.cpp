#include <QtGui>
#include <QApplication>
#include <QPushButton>
#include "qtdemo.h"
#include "avaspec.h"
#include "plot.h"
#include "timestamp.h"
#include "application.h"

Qtdemo::Qtdemo(QWidget *parent)
	: QDialog(parent)
{
    OpenCommBtn = new QPushButton(tr("Open Communication"));
    CloseCommBtn = new QPushButton(tr("Close Communication"));
    StartMeasBtn = new QPushButton(tr("Start Measurement"));
    StopMeasBtn = new QPushButton(tr("Stop Measurement"));
    TimeStampLabel = new QLabel(tr("Timestamp:"));
    timeStamp = new TimeStamp;
    IntTimeLabel = new QLabel(tr("Integration Time [ms]:"));
    edtIntTime = new QLineEdit("5.0");
    NumAvgLabel = new QLabel(tr("Number of Averages:"));
    edtNumAvg = new QLineEdit("1");
    NumMeasLabel = new QLabel(tr("Number of Measurements:"));;
    edtNumMeas = new QLineEdit("1");

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(OpenCommBtn);
    leftLayout->addWidget(CloseCommBtn);
    leftLayout->addWidget(StartMeasBtn);
    leftLayout->addWidget(StopMeasBtn);
    leftLayout->addWidget(TimeStampLabel);
    leftLayout->addWidget(timeStamp);
    leftLayout->addWidget(IntTimeLabel);
    leftLayout->addWidget(edtIntTime);
    leftLayout->addWidget(NumAvgLabel);
    leftLayout->addWidget(edtNumAvg);
    leftLayout->addWidget(NumMeasLabel);
    leftLayout->addWidget(edtNumMeas);
    leftLayout->addStretch();
    plot = new Plot(this);
	
    //QMessageBox::information(this, tr("QT4 Demo"),
    //                 QString("%1").arg(plot->maximumWidth()),
    //                 QMessageBox::Ok, QMessageBox::Ok);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(leftLayout,0,0,0);
    mainLayout->addWidget(plot,0,1,0);
    mainLayout->setRowStretch(2,10);
    mainLayout->setColumnStretch(3,10);
    setLayout(mainLayout);
    connect(OpenCommBtn, SIGNAL(clicked()), this, SLOT(on_OpenCommBtn_clicked()));
    connect(CloseCommBtn, SIGNAL(clicked()), this, SLOT(on_CloseCommBtn_clicked()));
    connect(StartMeasBtn, SIGNAL(clicked()), this, SLOT(on_StartMeasBtn_clicked()));
    connect(StopMeasBtn, SIGNAL(clicked()), this, SLOT(on_StopMeasBtn_clicked()));
    connect(qApp, SIGNAL(DataIsHere(int)), this, SLOT(on_DataIsHere(int)));
}

Qtdemo::~Qtdemo()
{

}

void Qtdemo::on_OpenCommBtn_clicked()
{
  int l_Port = AVS_Init(0);
  if (l_Port > 0) 
    QMessageBox::information(this, tr("QT4 Demo"),
           tr("Spectrometer detected"),
           QMessageBox::Ok, QMessageBox::Ok);
  else 
    QMessageBox::critical(this, tr("QT4 Demo"),
           tr("AVS_Init failed"),
           QMessageBox::Ok, QMessageBox::Ok);
  AvsIdentityType l_Active ;
  unsigned int l_reqsize;
  if (AVS_GetList(sizeof(AvsIdentityType), &l_reqsize, &l_Active) < 1)
      QMessageBox::critical(this, tr("QT4 Demo"),
         tr("AVS_GetList failed"),
         QMessageBox::Ok, QMessageBox::Ok);
  extern long m_DeviceHandle;
  m_DeviceHandle = AVS_Activate(&l_Active);
  extern unsigned short m_NrPixels;
  if (ERR_SUCCESS != AVS_GetNumPixels(m_DeviceHandle,&m_NrPixels))
	QMessageBox::critical(this, tr("QT4 Demo"),
           tr("AVS_GetNumPixels failed"),
           QMessageBox::Ok, QMessageBox::Ok);
  extern double m_pLambda[4096];
  if (ERR_SUCCESS != AVS_GetLambda(m_DeviceHandle,m_pLambda)) 
    QMessageBox::critical(this, tr("QT4 Demo"),
           tr("AVS_GetLambda failed"),
           QMessageBox::Ok, QMessageBox::Ok);
  plot->setAxisScale(plot->xBottom, m_pLambda[0], m_pLambda[m_NrPixels-1]);
  // set full scale
}

void Qtdemo::on_CloseCommBtn_clicked()
{
  AVS_Done();
}

void Qtdemo::on_StartMeasBtn_clicked()
{
    bool ok;
    MeasConfigType l_PrepareMeasData;
    l_PrepareMeasData.m_StartPixel = 0;
    extern unsigned short m_NrPixels;
    l_PrepareMeasData.m_StopPixel = m_NrPixels-1;
    QLocale::setDefault(QLocale::Dutch);
    double inttime = QString(edtIntTime->text()).toDouble(&ok);
    l_PrepareMeasData.m_IntegrationTime = inttime;
    l_PrepareMeasData.m_IntegrationDelay = 0;
    double numavg = QString(edtNumAvg->text()).toInt(&ok);
    l_PrepareMeasData.m_NrAverages = numavg;
    l_PrepareMeasData.m_CorDynDark.m_Enable = 0;
    l_PrepareMeasData.m_CorDynDark.m_ForgetPercentage = 0;
    l_PrepareMeasData.m_Smoothing.m_SmoothPix = 0;
    l_PrepareMeasData.m_Smoothing.m_SmoothModel = 0;
    l_PrepareMeasData.m_SaturationDetection = 0;
    l_PrepareMeasData.m_Trigger.m_Mode = 0;
    l_PrepareMeasData.m_Trigger.m_Source = 0;
    l_PrepareMeasData.m_Trigger.m_SourceType = 0;
    l_PrepareMeasData.m_Control.m_StrobeControl = 0;
    l_PrepareMeasData.m_Control.m_LaserDelay = 0;
    l_PrepareMeasData.m_Control.m_LaserWidth = 0;
    l_PrepareMeasData.m_Control.m_LaserWaveLength = 0;
    l_PrepareMeasData.m_Control.m_StoreToRam = 0;

    extern long m_DeviceHandle;
    int l_Res = AVS_PrepareMeasure(m_DeviceHandle,&l_PrepareMeasData);
    if (ERR_SUCCESS != l_Res) 
      QMessageBox::critical(this, tr("QT4 Demo"),
             tr("AVS_PrepareMeasure failed"),
             QMessageBox::Ok, QMessageBox::Ok);
    short l_NrOfScans = QString(edtNumMeas->text()).toInt(&ok);
//	HWND hwnd = (HWND)this->winId();
    // Start Measurement
    l_Res = AVS_MeasureCallback(m_DeviceHandle,&application::callback,l_NrOfScans);
    if (ERR_SUCCESS !=l_Res)
      QMessageBox::critical(this, tr("QT4 Demo"),
             tr("AVS_MeasureCallback failed"),
             QMessageBox::Ok, QMessageBox::Ok);
}
             
void Qtdemo::on_StopMeasBtn_clicked()
{
    extern long m_DeviceHandle;
    int l_Res = AVS_StopMeasure(m_DeviceHandle);
    if (ERR_SUCCESS != l_Res) 
      QMessageBox::critical(this, tr("QT4 Demo"),
             tr("AVS_StopMeasure failed"),
             QMessageBox::Ok, QMessageBox::Ok);
}

void Qtdemo::on_DataIsHere(int newValue)
{
    extern unsigned int l_Time;
    extern long m_DeviceHandle;
    extern double l_pSpectrum[MAX_NR_PIXELS];
    if (0 == newValue) {
        if (ERR_SUCCESS == AVS_GetScopeData(m_DeviceHandle,&l_Time,l_pSpectrum)) {
                timeStamp->repaint();
                plot->update_plot();
        }
    }

//  int ret = QMessageBox::information(this, tr("QT4 Demo"),
//              tr("Signal received"),
//              QMessageBox::Ok, QMessageBox::Ok);
}

