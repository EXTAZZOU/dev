#include <QApplication>
#include <iostream>
#include "controller/GameController.h"
#include "model/Minefield.h"
#include "view/ConsoleView.h"
#include "view/MainWindow.h"





int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// #ifdef WIN32
// #include <windows.h>
// int main(int argc, char *argv[]) {
//     AllocConsole();
//     freopen("CONOUT$", "w", stdout);
//     freopen("CONOUT$", "w", stderr);
// #else
// int main(int argc, char *argv[]) {
// #endif
//     Minefield minefield(9, 9, 10);
//     ConsoleView view(minefield);
//     GameController controller(minefield, view);

//     controller.run(std::cin); // Passer std::cin comme flux d'entrée

//     return 0;
// }
