#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fract.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->dimensionButton, SIGNAL(pressed()), this, SLOT(calcDimension()));
    connect(ui->scaleBox, SIGNAL(valueChanged(double)), this, SLOT(regenFractal()));
    connect(ui->iterationsBox, SIGNAL(valueChanged(int)), this, SLOT(regenFractal()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runAlgorithm()
{
    const float s = 0.0f;
    size_t x = 0, y = 0;
    const size_t
            iters = 1,
            w = algorithm.image.width(),
            h = algorithm.image.height();
    point_container input(w, h);

    for (const auto c : algorithm.pixels) {
        qreal r, g, b, a;
        c.getRgbF(&r, &g, &b, &a);
        const qreal avg = (r + g + b) / 3.0;
        if (x == w) {
            x = 0;
            y++;
        }
        input.set(x++, y, avg);
    }

#ifdef QT_DEBUG
    std::ofstream ddebugFile("debug_algorithm_output_BEFORE.txt", std::ios::out);
    for (auto i : ui->openGLWidget->vndata)
        ddebugFile << i << " ";
    ddebugFile.close();
#endif
    //ui->openGLWidget->vndata = multi_iter(input, iters, s).get();
    ui->openGLWidget->vndata = { 0.1, 0.1, 0.0, 0.2, 0.8, 0, 0.8, 0.1, 0.0 }; // DEBUG
    ui->openGLWidget->updateVertices();
    ui->openGLWidget->update();
#ifdef QT_DEBUG
    std::ofstream debugFile("debug_algorithm_output_AFTER.txt", std::ios::out);
    for (auto i : ui->openGLWidget->vndata)
        debugFile << i << " ";
    debugFile.close();
#endif
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
            runAlgorithm();
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
