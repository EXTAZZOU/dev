cmake_minimum_required(VERSION 3.14)
project(DemineurConsole)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Ajouter une option pour compiler en mode console ou GUI
option(BUILD_CONSOLE "Build as a console application" ON)

# Si BUILD_CONSOLE est activé, on ne définit pas WIN32 pour permettre l'exécution dans un terminal
if(BUILD_CONSOLE)
    add_executable(DemineurConsole
        model/Minefield.cpp model/Minefield.h
        view/ConsoleView.cpp view/ConsoleView.h
        controller/GameController.cpp controller/GameController.h
        main.cpp)
else()
    add_executable(DemineurConsole WIN32
        model/Minefield.cpp model/Minefield.h
        view/ConsoleView.cpp view/ConsoleView.h
        controller/GameController.cpp controller/GameController.h
        main.cpp)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

target_link_libraries(DemineurConsole PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
