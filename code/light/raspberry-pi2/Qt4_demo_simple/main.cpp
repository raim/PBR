#include <QtGui/QApplication>
#include "qtdemo.h"
#include "application.h"
#include "avaspec.h"

// globals

long m_DeviceHandle;
unsigned int l_Time=0;
unsigned short m_NrPixels;
double m_pLambda[MAX_NR_PIXELS];
double l_pSpectrum[MAX_NR_PIXELS];
// void* pt2application;

int main(int argc, char *argv[])
{
	application a(argc, argv);
        // pt2application = &a;
	Qtdemo *w = new Qtdemo;
//	w->resize(800,400);
	w->show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
