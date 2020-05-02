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
    QString fname=QFileDialog::getOpenFileName(this,"Select image file to open",QDir::homePath());

    ImageReader reader;

    kipl::io::ReadTIFF(img,fname.toStdString().c_str());


}
