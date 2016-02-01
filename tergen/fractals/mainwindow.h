#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "algorithm.h"
#include <QMainWindow>

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

private slots:
    void openFile();
};

#endif // MAINWINDOW_H
