#include <QtGui>
#include "application.h"
#include "avaspec.h"
#include "qtdemo.h"


application::application(int &argc, char *argv[])
	: QApplication(argc, argv)
{

}

void application::emitsignal()
{
        emit DataIsHere(0);
}

void application::callback(AvsHandle *handle, int *result )
{
    if (*result == 0) {
        // extern void* pt2application;
        // application *m = static_cast<application*>(pt2application);
        application *m = static_cast<application*>(qApp);
        // qApp is a predefined pointer to the QApplication instance
        if (m)
            m->emitsignal();
    }
}

//bool application::winEventFilter(MSG* msg, long* result)
//{
//	if (msg->message == WM_MEAS_READY)	{
//		if (ERR_SUCCESS == msg->wParam) {
//			emit DataIsHere(msg->wParam);
//		}
//		int ret = MessageBox(NULL, TEXT("QT4 Demo"), TEXT("Message received"), MB_OK);
//	}
//	result = 0;
//    return false;
//}
