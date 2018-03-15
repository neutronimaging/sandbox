#include "uxroiwidget.h"
#include "ui_uxroiwidget.h"

uxROIWidget::uxROIWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uxROIWidget)
{
    ui->setupUi(this);
    ui->spinX0->setValue(0);
    ui->spinX1->setValue(99);
    ui->spinX1->setMinimum(ui->spinX0->value()+1);
    ui->spinX0->setMaximum(ui->spinX1->value()-1);
    ui->spinY0->setValue(0);
    ui->spinY1->setValue(99);
    ui->spinY1->setMinimum(ui->spinY0->value()+1);
    ui->spinY0->setMaximum(ui->spinY1->value()-1);
}

uxROIWidget::~uxROIWidget()
{
    delete ui;
}

void uxROIWidget::setBoundingBox(int x0, int y0, int x1, int y1)
{
    ui->spinX0->setMinimum(x0);
    ui->spinX1->setMaximum(x1);
    ui->spinY0->setMinimum(y0);
    ui->spinY1->setMaximum(y1);
}

void uxROIWidget::setROI(int x0, int y0, int x1, int y1)
{

}

void uxROIWidget::setROI(int *roi)
{

}

void uxROIWidget::setROI(QRect rect)
{

}

void uxROIWidget::getROI(QRect &rect)
{

}

void uxROIWidget::getROI(int x0, int y0, int x1, int y1)
{

}

void uxROIWidget::getROI(int *roi)
{

}

void uxROIWidget::setLabel(const QString &lbl)
{
    ui->groupROI->setTitle(lbl);
}

void uxROIWidget::on_spinX0_valueChanged(int arg1)
{
    ui->spinX1->setMinimum(arg1+1);
}

void uxROIWidget::on_spinY0_valueChanged(int arg1)
{

}

void uxROIWidget::on_spinY1_valueChanged(int arg1)
{

}

void uxROIWidget::on_spinX1_valueChanged(int arg1)
{

}
