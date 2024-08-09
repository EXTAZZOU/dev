#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>

// Constructeur de MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), timeElapsed(0) {
    ui->setupUi(this);

    minefield = new Minefield(9, 9, 10);

    // Configuration du label de chronomètre
    timerLabel = new QLabel("Time: 00:00", this);
    timerLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    timer->start(1000);

    // Configuration du bouton "Recommencer"
    resetButton = new QPushButton("Recommencer", this);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    // Configuration de la grille de boutons
    gridLayout = new QGridLayout(this);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            buttons[i][j] = new QPushButton(this);
            buttons[i][j]->setFixedSize(40, 40);
            gridLayout->addWidget(buttons[i][j], i, j);

            buttons[i][j]->installEventFilter(this);
        }
    }

    // Configuration du layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(timerLabel);
    mainLayout->addWidget(resetButton, 0, Qt::AlignCenter);
    mainLayout->addLayout(gridLayout);
    setCentralWidget(new QWidget());
    centralWidget()->setLayout(mainLayout);
}

// Destructeur de MainWindow
MainWindow::~MainWindow() {
    delete ui;
    delete minefield;
}

// Met à jour le chronomètre
void MainWindow::updateTimer() {
    timeElapsed++;
    int minutes = timeElapsed / 60;
    int seconds = timeElapsed % 60;
    timerLabel->setText(QString("Time: %1:%2")
                            .arg(minutes, 2, 10, QLatin1Char('0'))
                            .arg(seconds, 2, 10, QLatin1Char('0')));
}

// Réinitialise le jeu
void MainWindow::resetGame() {
    timer->stop();
    timeElapsed = 0;
    timerLabel->setText("Time: 00:00");
    timer->start(1000);
    resetMinefield();
}

// Réinitialise le champ de mines
void MainWindow::resetMinefield() {
    delete minefield;
    minefield = new Minefield(9, 9, 10);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            buttons[i][j]->setText("");
            buttons[i][j]->setStyleSheet("");
            buttons[i][j]->setEnabled(true);
        }
    }
}

// Gère les événements sur les boutons
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (watched == buttons[i][j] && event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::RightButton) {
                    if (minefield->isMarked(i, j)) {
                        minefield->unmark(i, j);
                        buttons[i][j]->setStyleSheet("");
                    } else {
                        minefield->mark(i, j);
                        buttons[i][j]->setStyleSheet("background-image: url(C:/Users/extaz/Desktop/Demineur/images/mark.png);");
                    }
                    return true;
                } else if (mouseEvent->button() == Qt::LeftButton) {
                    if (!minefield->isRevealed(i, j)) {
                        minefield->reveal(i, j);
                        revealAdjacent(i, j);
                        if (minefield->isGameLost()) {
                            revealAll();
                            timer->stop();
                            QMessageBox::information(this, "Game Over", "Tu as touché une mine!");
                            resetGame();
                        } else if (minefield->isGameWon()) {
                            revealAll();
                            timer->stop();
                            QMessageBox::information(this, "Bravo", "Vous avez gagné la partie!");
                        }
                    }
                    return true;
                }
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

// Met à jour l'affichage d'un bouton
void MainWindow::updateButton(int x, int y) {
    if (minefield->isRevealed(x, y)) {
        buttons[x][y]->setStyleSheet("background-color: lightgray;");

        if (minefield->hasMine(x, y)) {
            buttons[x][y]->setStyleSheet("background-color: lightgray; background-image: url(C:/Users/extaz/Desktop/Demineur/images/bomb.png);");
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

// Révèle toutes les cases adjacentes
void MainWindow::revealAdjacent(int x, int y) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (minefield->isRevealed(i, j)) {
                updateButton(i, j);
            }
        }
    }
}

// Révèle toutes les cases après la fin du jeu
void MainWindow::revealAll() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (minefield->hasMine(i, j)) {
                buttons[i][j]->setStyleSheet("background-color: lightgray; background-image: url(C:/Users/extaz/Desktop/Demineur/images/bomb.png);");
            } else {
                updateButton(i, j);
            }
        }
    }
}
