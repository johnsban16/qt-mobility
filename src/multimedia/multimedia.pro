TEMPLATE = lib

# distinct from QtMultimedia
TARGET = QtMedia

include (../../common.pri)
INCLUDEPATH+= .

QT += network

contains(QT_CONFIG, opengl): QT += opengl

!static:DEFINES += QT_MAKEDLL
DEFINES += QT_BUILD_MEDIA_LIB

PRIVATE_HEADERS += \
    qmediacontrol_p.h \
    qmediaobject_p.h \
    qmediaservice_p.h  \
    qmediaplaylist_p.h \
    qmediaplaylistprovider_p.h \
    qmediaimageviewerservice_p.h \
    qvideowidget_p.h \
    qmediapluginloader_p.h


PUBLIC_HEADERS += \
    qmediacontrol.h \
    qmediaobject.h \
    qmediaservice.h \
    qlocalmediaplaylistprovider.h \
    qmediaimageviewer.h \
    qmediaplayer.h \
    qmediaplayercontrol.h \
    qmediaplaylist.h \
    qmediaplaylistnavigator.h \
    qmediaplaylistprovider.h \
    qmediaplaylistioplugin.h \
    qmediacontent.h \
    qmediaresource.h \
    qmediarecorder.h \
    qmediaencodersettings.h \
    qmediarecordercontrol.h \
    qmediaserviceprovider.h \
    qmediaserviceproviderplugin.h \
    qmetadatacontrol.h \
    qmediastreamscontrol.h \
    qradiotuner.h \
    qradiotunercontrol.h \
    qtmedianamespace.h \
    qvideooutputcontrol.h \
    qvideowidget.h \
    qvideowindowcontrol.h \
    qvideowidgetcontrol.h \
    qaudioencodercontrol.h \
    qvideoencodercontrol.h \
    qimageencodercontrol.h \
    qaudiocapturesource.h \
    qmediaformatcontrol.h \
    qmediaplaylistcontrol.h \
    qaudiodevicecontrol.h \
    qvideodevicecontrol.h


SOURCES += qmediacontrol.cpp \
    qmediaobject.cpp \
    qmediaservice.cpp \
    qlocalmediaplaylistprovider.cpp \
    qmediaimageviewer.cpp \
    qmediaimageviewerservice.cpp \
    qmediaplayer.cpp \
    qmediaplayercontrol.cpp \
    qmediaplaylist.cpp \
    qmediaplaylistioplugin.cpp \
    qmediaplaylistnavigator.cpp \
    qmediaplaylistprovider.cpp \
    qmediarecorder.cpp \
    qmediaencodersettings.cpp \
    qmediarecordercontrol.cpp \
    qmediacontent.cpp \
    qmediaresource.cpp \
    qmediaserviceprovider.cpp \
    qmetadatacontrol.cpp \
    qmediastreamscontrol.cpp \
    qradiotuner.cpp \
    qradiotunercontrol.cpp \
    qvideooutputcontrol.cpp \
    qvideowidget.cpp \
    qvideowindowcontrol.cpp \
    qvideowidgetcontrol.cpp \
    qaudioencodercontrol.cpp \
    qvideoencodercontrol.cpp \
    qimageencodercontrol.cpp \
    qaudiocapturesource.cpp \
    qmediaformatcontrol.cpp \
    qmediaplaylistcontrol.cpp \
    qaudiodevicecontrol.cpp \
    qvideodevicecontrol.cpp \
    qmediapluginloader.cpp

contains(QT_CONFIG, multimedia) {
    PUBLIC_HEADERS += \
        qgraphicsvideoitem.h \
        qvideorenderercontrol.h

    PRIVATE_HEADERS += \
        qpaintervideosurface_p.h

    SOURCES += \
        qgraphicsvideoitem.cpp \
        qpaintervideosurface.cpp \
        qvideorenderercontrol.cpp
} else {
    PUBLIC_HEADERS += qaudioformat.h
    SOURCES += qaudioformat.cpp
}

include (experimental/experimental.pri)
HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS

symbian {
    QtMediaDeployment.sources = QtMedia.dll
    QtMediaDeployment.path = /sys/bin
    DEPLOYMENT += QtMediaDeployment
    TARGET.CAPABILITY = ALL -TCB
}

include(../../features/deploy.pri)