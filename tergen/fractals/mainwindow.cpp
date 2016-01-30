#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
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
            ui->statusBar->showMessage("File loaded successfully.");
    }
}
