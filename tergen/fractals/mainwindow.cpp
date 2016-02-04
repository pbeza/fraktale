#include <QFileDialog>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runAlgorithm()
{
    const size_t iters = 2;
    const float s = 0.0f;
    const size_t w = algorithm.image.width(), h = algorithm.image.height();
    point_container input(w, h), output(w, h);
    size_t x = 0, y = 0;

    // Normalize RGBA

    for (const auto c : algorithm.pixels) {
        qreal r, g, b, a;
        c.getRgbF(&r, &g, &b, &a);
        const qreal avg = (r + g + b) / 3.0;
        if (x == w) {
            x = 0;
            y++;
        }
        input.set(x++, y, avg);
        qDebug() << "(" << r << ", " << g << ", " << b << ") = avg = " << avg;
    }
    output = multi_iter(input, iters, s);
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
