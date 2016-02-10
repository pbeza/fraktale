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
    connect(ui->xAxisVerticalSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setXRotation(int)));
    connect(ui->openGLWidget, SIGNAL(xRotationChanged(int)), ui->xAxisVerticalSlider, SLOT(setValue(int)));
    connect(ui->yAxisVerticalSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setYRotation(int)));
    connect(ui->openGLWidget, SIGNAL(yRotationChanged(int)), ui->yAxisVerticalSlider, SLOT(setValue(int)));
    connect(ui->zAxisVerticalSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setZRotation(int)));
    connect(ui->openGLWidget, SIGNAL(zRotationChanged(int)), ui->zAxisVerticalSlider, SLOT(setValue(int)));
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
            iters = ui->iterationsBox->text().toInt(),
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
    result_point_container = multi_iter(input, iters, s);
    auto &vec = result_point_container.get();
    auto &vndata = ui->openGLWidget->vndata;
    vndata.clear();
    vndata.resize(vec.size() * 3);
    for(size_t xx = 0; xx < result_point_container.w(); xx++) {
        for(size_t yy = 0; yy < result_point_container.h(); yy++) {
            size_t index = 3 * (xx * result_point_container.h() + yy);
            vndata[index + 0] = (float)xx / result_point_container.w();
            vndata[index + 1] = (float)yy / result_point_container.h();
            vndata[index + 2] = vec[xx * result_point_container.h() + yy];
        }
    }
    ui->openGLWidget->updateVertices();
    ui->openGLWidget->update();
#ifdef QT_DEBUG
    std::ofstream debugFile("debug_algorithm_output_AFTER.txt", std::ios::out);
    for (auto i : ui->openGLWidget->vndata)
        debugFile << i << " ";
    debugFile.close();
#endif
    computed = true;
}

void MainWindow::openFile()
{
    QFileDialog dialog;
    QStringList mimeTypeFilters;
    mimeTypeFilters << "image/png" << "image/jpeg";
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
    runAlgorithm();
}

void MainWindow::calcDimension()
{
    if (!computed) {
        QMessageBox::information(NULL, "Image not selected", "Select image before calculating dimension.");
        return;
    }
    int dim = ui->dimensionSubdiv->text().toInt();
    float dimension = box_dimension( result_point_container, dim );
    QMessageBox::information(NULL, "Dimension result", "Dimension equals = " + QString::number(dimension));
}
