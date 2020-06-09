#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QDir>

#include <imagereader.h>
#include <io/io_tiff.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionLoad_triggered()
{
    QString fname=QFileDialog::getOpenFileName(this,"Select image file to open",QDir::homePath()+QString("/repos/imagingsuite/core/kipl/UnitTests/data"));

    kipl::io::ReadTIFF(img,fname.toStdString().c_str());
    ui->widget->setVolume(img);
}

void MainWindow::on_pushButtonRenderSphere_clicked()
{
    size_t dims[]={static_cast<size_t>(ui->spinBoxX->value()),
                   static_cast<size_t>(ui->spinBoxY->value()),
                   static_cast<size_t>(ui->spinBoxZ->value())};

    img = kipl::base::TImage<float,3>(dims);

    ptrdiff_t midX = dims[0]/2;
    ptrdiff_t midY = dims[1]/2;
    ptrdiff_t midZ = dims[2]/2;

    ptrdiff_t radius = std::min(midX,std::min(midY,midZ))*0.8;
    radius = radius * radius;
    size_t idx = 0;

    float *pImg = img.GetDataPtr();
    for (ptrdiff_t z=-midZ; z < midZ; ++z)
    {
        for (ptrdiff_t y=-midY; y < midY; ++y)
        {
            for (ptrdiff_t x=-midX; x < midX; ++x, ++idx)
            {
                pImg[idx] = (x*x + y*y + z*z) < radius;
            }
        }
    }

    ui->widget->setVolume(img);
}

void MainWindow::on_pushButton_clicked()
{
    QString fname=QDir::homePath()+QString("/git/imagingsuite/core/kipl/UnitTests/data/multiframe.tif");

    kipl::io::ReadTIFF(img,fname.toStdString().c_str());
    ui->widget->setVolume(img);
}
