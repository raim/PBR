DEFINES += QWT_DLL
TEMPLATE = app
HEADERS = application.h \
    qtdemo.h \
    timestamp.h \
    plot.h \
    ex5216.h \
    devices.h \
    device.h
SOURCES = application.cpp \
    main.cpp \
    qtdemo.cpp \
    plot.cpp \
    timestamp.cpp \
    devices.cpp \
    device.cpp
LIBS += -lavs \
    -lqwt
