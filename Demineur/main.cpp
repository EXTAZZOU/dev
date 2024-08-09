#include <QApplication>
#include "view/MainWindow.h"

// Fonction principale
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);  // Initialise l'application Qt
    MainWindow w;  // Crée la fenêtre principale de l'application
    w.show();  // Affiche la fenêtre principale
    return a.exec();  // Entre dans la boucle d'événements Qt
}
