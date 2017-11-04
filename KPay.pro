QT += qml quick sql widgets network

CONFIG += c++11

SOURCES += main.cpp \
    engineprovider.cpp \
    kpaymainwindow.cpp \
    engines/btc-electrum/btcelectrumengine.cpp \
    engines/ltc-electrum/ltcelectrumengine.cpp \
    utils.cpp \
    engineinterface.cpp \
    engines/btc-electrum/btcelectrumwallet.cpp \
    engines/electrumengine.cpp \
    engines/electrumwallet.cpp

RESOURCES += resources/resources.qrc \
    engines/btc-electrum/resources/btcelectrum.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    engineinterface.h \
    engineprovider.h \
    kpaymainwindow.h \
    walletinterface.h \
    engines/btc-electrum/btcelectrumengine.h \
    engines/ltc-electrum/ltcelectrumengine.h \
    utils.h \
    engines/btc-electrum/btcelectrumwallet.h \
    engines/electrumengine.h \
    engines/electrumwallet.h
