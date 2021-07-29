QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FORM/logindialog.cpp \
    FORM/basis_demo/filewindow.cpp \
    FORM/http_demo/httpdemo.cpp \
    main.cpp \
    FORM/mainwindow.cpp \
    FORM/basis_demo/mytimer.cpp \
    FORM/graph_demo/painter.cpp \
    FORM/sql_demo/qtsql.cpp \
    FORM/sql_demo/sqldialog.cpp \
    SOURCE/db_help/dbconnect.cpp \
    SOURCE/db_help/dbconnectpool.cpp \
    FORM/http_demo/tcpsocket.cpp \
    FORM/http_demo/tcpclient.cpp

HEADERS += \
    FORM/mainwindow.h \
    FORM/logindialog.h \
    FORM/basis_demo/filewindow.h \
    FORM/basis_demo/mytimer.h \
    FORM/graph_demo/painter.h \
    FORM/sql_demo/qtsql.h \
    FORM/sql_demo/sqldialog.h \
    SOURCE/db_help/dbconnect.h \
    SOURCE/db_help/dbconnectpool.h \
    FORM/http_demo/httpdemo.h \
    FORM/http_demo/tcpsocket.h \
    FORM/http_demo/tcpclient.h

FORMS += \
    FORM/mainwindow.ui \
    FORM/logindialog.ui \
    FORM/basis_demo/filewindow.ui \
    FORM/basis_demo/mytimer.ui \
    FORM/graph_demo/painter.ui \
    FORM/sql_demo/qtsql.ui \
    FORM/sql_demo/sqldialog.ui \
    FORM/http_demo/httpdemo.ui \
    FORM/http_demo/tcpsocket.ui \
    FORM/http_demo/tcpclient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


