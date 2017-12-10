#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "avaspec.h"

class application : public QApplication
{
	Q_OBJECT

public:
	application(int &argc, char *argv[]);
        // bool winEventFilter(MSG* msg, long* result);
        void emitsignal();
        static void callback(AvsHandle *handle, int *result );

signals:
	void DataIsHere(int newValue);
};

#endif // APPLICATION_H
