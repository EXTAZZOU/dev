cmake_minimum_required(VERSION 3.14)
project(Demineur)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(DemineurConsole
    model/Minefield.cpp model/Minefield.h
    view/ConsoleView.cpp view/ConsoleView.h
    controller/GameController.cpp controller/GameController.h
    main.cpp
    view/MainWindow.cpp view/MainWindow.h
    view/MainWindow.h view/MainWindow.cpp view/MainWindow.ui
    images/mark.png)

target_link_libraries(DemineurConsole PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

