TARGET = rockpool

include(../version.pri)

QT += qml quick dbus

CONFIG += c++11
CONFIG += sailfishapp

PKGCONFIG += qt5embedwidget

HEADERS += \
    notificationsourcemodel.h \
    servicecontrol.h \
    pebble.h \
    pebbles.h \
    applicationsmodel.h \
    applicationsfiltermodel.h \
    appstoreclient.h \
    screenshotmodel.h

SOURCES += main.cpp \
    notificationsourcemodel.cpp \
    servicecontrol.cpp \
    pebble.cpp \
    pebbles.cpp \
    applicationsmodel.cpp \
    applicationsfiltermodel.cpp \
    appstoreclient.cpp \
    screenshotmodel.cpp

RESOURCES += rockwork.qrc

QML_FILES += $$files(qml/*.qml,true)
QML_FILES += $$files(qml/pages/*.qml,true)
QML_FILES += $$files(qml/cover/*.qml,true)

CONF_FILES +=  rockpool.png \
               rockpool.desktop \
               $$files(translations/*.ts,true)

JSM_FILES += $$files(jsm/*.manifest,true)
JSM_FILES += $$files(jsm/*.js,true)

#show all the files in QtCreator
OTHER_FILES += $${QML_FILES} \
               $${JSM_FILES} \
               $${CONF_FILES}

#specify where the qml files are installed to
qml.path = /usr/share/rockpool/qml
qml.files += $${QML_FILES}

#and the app icon
icon.path = /usr/share/icons/hicolor/86x86/apps/
icon.files = rockpool.png

# Default rules for deployment.
target.path = /usr/bin

# gecko js modules
jsm.path = /usr/share/rockpool/jsm
jsm.files += $${JSM_FILES}

DISTFILES += JSM_FILES
INSTALLS += jsm

## These are pre-defined rules, don't need explicit mentioning
#INSTALLS+=target icon qml
CONFIG(debug, debug|release) {
    DEFINES += 'ROCKPOOL_DATA_PATH=\\"/opt/sdk/rockpool/usr/share/rockpool/\\"'
}
# Translations
lupdate_only {
    SOURCES += QML_FILES
}
CONFIG += sailfishapp_i18n
TRANSLATIONS += $$files(translations/*.ts,true)
