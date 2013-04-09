TEMPLATE = app
CONFIG += console
CONFIG -= qt

# LIBS += -L../plant-build \
LIBS += -L../my-little-plant-release \
        -lmy-little-plant

INCLUDEPATH += ../my-little-plant

SOURCES += main.cpp \
    controller/controllerpid.cpp \
    controller/controller.cpp \
    controller/object/modeldata.cpp \
    controller/controllerrst.cpp \
    controller/controllerapzp1.cpp \
    controller/identification/arxidentification.cpp \
    controller/gainschedulingpid.cpp \
    controller/identification/modelidentification.cpp \
    controller/controllergpc.cpp \
    controller/object/discreteobject.cpp \
    simulator/simulator.cpp \
    simulator/simulatora.cpp \
    simulator/simulatorb.cpp

HEADERS += \
    controller/controllerpid.h \
    controller/controller.h \
    controller/object/modeldata.h \
    tool.h \
    controller/controllerrst.h \
    controller/controllerapzp1.h \
    controller/identification/arxidentification.h \
    controller/gainschedulingpid.h \
    controller/identification/modelidentification.h \
    controller/controllergpc.h \
    controller/object/discreteobject.h \
    simulator/simulator.h \
    simulator/simulatora.h \
    simulator/simulatorb.h

OTHER_FILES += \
    controller/pid/Dokument bez nazwy

