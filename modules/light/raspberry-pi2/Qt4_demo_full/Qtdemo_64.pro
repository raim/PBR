DEFINES += QWT_DLL
TEMPLATE = app
FORMS = analog_io.ui \
    digital_io.ui \
    eeprom.ui \ 
    qtdemo_64.ui 
HEADERS = application.h \
    qtdemo_64.h \
    analog_io.h \
    digital_io.h \
    eeprom.h \
    plot.h \
    avaspec.h
SOURCES = application.cpp \
    main.cpp \
    qtdemo_64.cpp \
    analog_io.cpp \
    digital_io.cpp \
    eeprom.cpp \
    plot.cpp
LIBS += -lavs \
    -lqwt
