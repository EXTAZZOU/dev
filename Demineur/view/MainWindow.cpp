#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timeElapsed(0) {
    ui->setupUi(this);

    minefield = new Minefield(9, 9, 10);  // Créer un champ de mines de 9x9 avec 10 mines

    // Configuration du chronomètre
    timerLabel = new QLabel("Time: 00:00", this);
    timerLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timer->start(1000);  // Met à jour chaque seconde

    // Configuration du bouton "Recommencer"
    resetButton = new QPushButton("Recommencer", this);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    gridLayout = new QGridLayout(this);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            buttons[i][j] = new QPushButton(this);
            buttons[i][j]->setFixedSize(40, 40);
            gridLayout->addWidget(buttons[i][j], i, j);

            buttons[i][j]->installEventFilter(this);
        }
    }

    // Ajouter le timerLabel et le resetButton au layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(timerLabel);
    mainLayout->addWidget(resetButton, 0, Qt::AlignCenter);  // Centrer le bouton "Recommencer"
    mainLayout->addLayout(gridLayout);
    setCentralWidget(new QWidget());
    centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow() {
    delete ui;
    delete minefield;
}

void MainWindow::updateTimer() {
    timeElapsed++;
    int minutes = timeElapsed / 60;
    int seconds = timeElapsed % 60;
    timerLabel->setText(QString("Time: %1:%2")
                            .arg(minutes, 2, 10, QLatin1Char('0'))
                            .arg(seconds, 2, 10, QLatin1Char('0')));
}

void MainWindow::resetGame() {
    timer->stop();  // Arrêter le chronomètre
    timeElapsed = 0;
    timerLabel->setText("Time: 00:00");
    timer->start(1000);  // Redémarrer le chronomètre
    resetMinefield();  // Réinitialiser le champ de mines
}

void MainWindow::resetMinefield() {
    delete minefield;
    minefield = new Minefield(9, 9, 10);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            buttons[i][j]->setText("");
            buttons[i][j]->setStyleSheet("");  // Réinitialiser à l'état par défaut
            buttons[i][j]->setEnabled(true);
        }
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (watched == buttons[i][j] && event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::RightButton) {
                    if (minefield->isMarked(i, j)) {
                        minefield->unmark(i, j);
                        buttons[i][j]->setStyleSheet("");  // Réinitialiser à l'état non marqué
                    } else {
                        minefield->mark(i, j);
                        buttons[i][j]->setStyleSheet("background-image: url(C:/Users/ilias/Documents/abc/Demineur/images/mark.png);");
                    }
                    return true;
                } else if (mouseEvent->button() == Qt::LeftButton) {
                    if (!minefield->isRevealed(i, j)) {
                        minefield->reveal(i, j);
                        revealAdjacent(i, j);  // Révéler toutes les cases adjacentes
                        if (minefield->isGameLost()) {
                            revealAll();
                            timer->stop();  // Arrêter le chronomètre à la fin du jeu
                            QMessageBox::information(this, "Game Over", "Tu as touché une mine!");
                        } else if (minefield->isGameWon()) {
                            revealAll();
                            timer->stop();  // Arrêter le chronomètre à la fin du jeu
                            QMessageBox::information(this, "Bravo", "Vous avez gagner la partie!");
                        }
                    }
                    return true;
                }
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updateButton(int x, int y) {
    if (minefield->isRevealed(x, y)) {
        buttons[x][y]->setStyleSheet("background-color: lightgray;");

        if (minefield->hasMine(x, y)) {
            buttons[x][y]->setStyleSheet("background-color: lightgray; background-image: url(C:/Users/ilias/Documents/abc/Demineur/images/bomb.png);");
        } else {
            int neighboringMines = minefield->getNeighboringMines(x, y);
            if (neighboringMines > 0) {
                buttons[x][y]->setText(QString::number(neighboringMines));
            } else {
                buttons[x][y]->setText("");
            }
        }
        buttons[x][y]->setEnabled(false);
    }
}

void MainWindow::revealAdjacent(int x, int y) {
    // Parcours toutes les cases et applique le style de case révélée
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (minefield->isRevealed(i, j)) {
                updateButton(i, j);
            }
        }
    }
}

void MainWindow::revealAll() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (minefield->hasMine(i, j)) {
                buttons[i][j]->setStyleSheet("background-color: lightgray; background-image: url(C:/Users/ilias/Documents/abc/Demineur/images/bomb.png);");
            } else {
                updateButton(i, j);
            }
        }
    }
}
