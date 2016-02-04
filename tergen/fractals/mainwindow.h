#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Logic::Algorithm algorithm;
    void runAlgorithm();

private slots:
    void openFile();
    void regenFractal();
    void calcDimension();
};

#endif // MAINWINDOW_H
