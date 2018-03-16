#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cnt(0)
{
    ui->setupUi(this);
    ui->widget->setTitle("My ROI");
    connect(ui->widget,&uxROIWidget::getROIClicked,this,&MainWindow::getROIclicked);
    connect(ui->widget,&uxROIWidget::valueChanged,this,&MainWindow::on_valueChanged);

    ui->widget->setROIColor("red");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getROIclicked()
{
    ui->checkBox->setChecked(!ui->checkBox->isChecked());
    ui->spinBox->setValue(++cnt);
    std::ostringstream msg;

    msg<<"cnt="<<cnt;
    ui->label->setText(QString::fromStdString(msg.str()));
    qDebug("%s",msg.str().c_str());
}

void MainWindow::on_valueChanged(int x0,int y0, int x1, int y1)
{
    std::ostringstream msg;

    msg<<x0<<", "<<y0<<", "<<x1<<", "<<y1;
    ui->label->setText(QString::fromStdString(msg.str()));
}

void MainWindow::on_pushButton_clicked()
{
    ui->checkBox->setChecked(!ui->checkBox->isChecked());

    ui->spinBox->setValue(cnt);
}

