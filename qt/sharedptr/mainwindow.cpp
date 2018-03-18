#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qrect.h>
#include <qpainter.h>
#include <qpen.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rect_(new QRectF)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    *rect_ = QRectF(100,100,10,10);

//    QPainter painter();

//    // So that we can use the background color
//    // Otherwise the background is transparent
//    painter.setBackgroundMode(Qt::OpaqueMode);

//    // Smooth out the circle
//    painter.setRenderHint(QPainter::Antialiasing);

//    // Use background color
//    painter.setBrush(painter.background());

//    // Get current pen before resetting so we have
//    // access to the color() method which returns the
//    // color from the stylesheet
//    QPen textPen = painter.pen();


}
