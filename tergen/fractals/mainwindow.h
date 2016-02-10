#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithm.h"
#include "fract.h"

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
    point_container result_point_container;
    void runAlgorithm();
    bool computed = false;

private slots:
    void openFile();
    void regenFractal();
    void calcDimension();
};

#endif // MAINWINDOW_H
