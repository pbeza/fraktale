#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->dimButton, SIGNAL(pressed()), this, SLOT(calcDimension()));
    connect(ui->sBox, SIGNAL(valueChanged(double)), this, SLOT(regenFractal()));
    connect(ui->iterBox, SIGNAL(valueChanged(int)), this, SLOT(regenFractal()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QFileDialog dialog;
    QStringList mimeTypeFilters;
    mimeTypeFilters << "image/jpeg" << "image/png";
    dialog.setMimeTypeFilters(mimeTypeFilters);
    if (QDialog::Accepted == dialog.exec())
    {
        QString fileName = dialog.selectedFiles().first();
        if (!fileName.isEmpty())
        {
            algorithm.setImage(fileName);
            ui->statusBar->showMessage("File loaded successfully.");
        }
    }
}

void MainWindow::regenFractal()
{
    QMessageBox::information(NULL, "Hello World!", "Regen!");
}

void MainWindow::calcDimension()
{
    QMessageBox::information(NULL, "Hello World!", "Calc!");
}
