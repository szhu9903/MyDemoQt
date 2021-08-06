cmake_minimum_required(VERSION 3.19)
project(myDemoQT)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.2/lib/cmake")
#set(CMAKE_PREFIX_PATH "/Users/zhushuaijie/Qt5.12.11/5.12.11/clang_64/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Sql Widgets Network REQUIRED)

set(
        SOURCES
        main.cpp
        FORM/mainwindow.cpp
        FORM/logindialog.cpp
        FORM/basis_demo/mytimer.cpp
        FORM/basis_demo/filewindow.cpp
        FORM/graph_demo/painter.cpp
        FORM/http_demo/httpdemo.cpp
        FORM/http_demo/tcpsocket.cpp
        FORM/http_demo/tcpclient.cpp
        FORM/http_demo/tcpsender.cpp
        FORM/sql_demo/qtsql.cpp
        FORM/sql_demo/sqldialog.cpp
        SOURCE/db_help/dbconnect.cpp
        SOURCE/db_help/dbconnectpool.cpp)
set(
        HEADERS
        FORM/mainwindow.h
        FORM/logindialog.h
        FORM/basis_demo/mytimer.h
        FORM/basis_demo/filewindow.h
        FORM/graph_demo/painter.h
        FORM/http_demo/httpdemo.h
        FORM/http_demo/tcpsocket.h
        FORM/http_demo/tcpclient.h
        FORM/http_demo/tcpsender.h
        FORM/sql_demo/qtsql.h
        FORM/sql_demo/sqldialog.h
        SOURCE/db_help/dbconnect.h
        SOURCE/db_help/dbconnectpool.h)
set(
        UI
        FORM/mainwindow.ui
        FORM/logindialog.ui
        FORM/basis_demo/mytimer.ui
        FORM/basis_demo/filewindow.ui
        FORM/graph_demo/painter.ui
        FORM/http_demo/httpdemo.ui
        FORM/http_demo/tcpsocket.ui
        FORM/http_demo/tcpclient.ui
        FORM/http_demo/tcpsender.ui
        FORM/sql_demo/qtsql.ui
        FORM/sql_demo/sqldialog.ui)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(
        ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Sql
        Qt5::Network
        Qt5::Widgets)

