TEMPLATE = app
CONFIG+=testcase
TARGET=tst_qgeosatelliteinfosource

include (../../../../common.pri)

INCLUDEPATH += ../../../../src/location

SOURCES += tst_qgeosatelliteinfosource.cpp \
        ../../testqgeosatelliteinfosource.cpp \
        ../../qlocationtestutils.cpp \

HEADERS += ../../testqgeosatelliteinfosource_p.h \
        ../../qlocationtestutils_p.h \

CONFIG += mobility
MOBILITY = location

meego: contains (gypsy_enabled, yes) {
    DEFINES += TST_GYPSYMOCK_ENABLED=1
    INCLUDEPATH += ../gypsymock
    RESOURCES += ../gypsymock/gypsy_mock_data.qrc
    # needs to be compiled because we use private symbols (init):
    HEADERS += ../../../../src/location/qgeosatelliteinfosource_gypsy_p.h
    HEADERS += ../gypsymock/gypsymock.h
    SOURCES += ../../../../src/location/qgeosatelliteinfosource_gypsy.cpp
    SOURCES += ../gypsymock/gypsymock.cpp
    CONFIG += qdbus link_pkgconfig
    PKGCONFIG += gconf-2.0 glib-2.0 gypsy
    QMAKE_PKGCONFIG_REQUIRES += glib-2.0 gconf-2.0 gypsy
    pkgconfig.path = $$QT_MOBILITY_LIB/pkgconfig
    pkgconfig.files = QtLocation.pc
}

symbian {
    TARGET.CAPABILITY = ALL -TCB
}
