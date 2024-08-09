#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include "../model/Minefield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void updateTimer();
    void resetGame();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    Minefield *minefield;
    QPushButton *buttons[9][9];
    QLabel *timerLabel;
    QTimer *timer;
    int timeElapsed;
    QPushButton *resetButton;

    void setupMinefield();
    void updateButton(int x, int y);
    void revealAll();
    void resetMinefield();
    void revealAdjacent(int x, int y);
};

#endif // MAINWINDOW_H
