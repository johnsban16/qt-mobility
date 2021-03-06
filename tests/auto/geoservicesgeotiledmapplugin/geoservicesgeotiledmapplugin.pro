TEMPLATE = lib
CONFIG += plugin testplugin
TARGET = $$qtLibraryTarget(qtgeoservices_tiledgeomapplugin)
PLUGIN_TYPE=geoservices

include(../../../common.pri)

CONFIG += mobility
MOBILITY = location

HEADERS += qgeomappingmanagerengine_test.h \
            qgeoserviceproviderplugin_test.h

SOURCES += qgeoserviceproviderplugin_test.cpp


INCLUDEPATH += ../../../src/location \
                ../../../src/location/maps \
                ../../../src/location/maps/tiled

RESOURCES += geoservicestestmaptiles.qrc

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
    pluginDep.sources = $${TARGET}.dll
    pluginDep.path = $${QT_PLUGINS_BASE_DIR}/$${PLUGIN_TYPE}
    DEPLOYMENT += pluginDep      
}
