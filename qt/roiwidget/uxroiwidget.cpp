#include "uxroiwidget.h"
#include "ui_uxroiwidget.h"

uxROIWidget::uxROIWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uxROIWidget)
{
    ui->setupUi(this);
    setROI(0,0,100,100);
}

uxROIWidget::~uxROIWidget()
{
    delete ui;
}

void uxROIWidget::setBoundingBox(int x0, int y0, int x1, int y1, bool updateFields)
{
    ui->spinX0->setMinimum(std::min(x0,x1));
    ui->spinX0->setMaximum(std::max(x0,x1));

    ui->spinX1->setMinimum(std::min(x0,x1));
    ui->spinX1->setMaximum(std::max(x0,x1));

    ui->spinY0->setMinimum(std::min(y0,y1));
    ui->spinY0->setMaximum(std::max(y0,y1));

    ui->spinY1->setMinimum(std::min(y0,y1));
    ui->spinY1->setMaximum(std::max(y0,y1));
    if (updateFields) {
        setROI(x0,y0,x1,y1);
    }
}

void uxROIWidget::setROI(int x0, int y0, int x1, int y1)
{
    ui->spinX0->setValue(std::min(x0,x1));
    ui->spinX1->setValue(std::max(x0,x1));
    ui->spinX1->setMinimum(ui->spinX0->value()+1);
    ui->spinX0->setMaximum(ui->spinX1->value()-1);
    ui->spinY0->setValue(std::min(y0,y1));
    ui->spinY1->setValue(std::max(y0,y1));
    ui->spinY1->setMinimum(ui->spinY0->value()+1);
    ui->spinY0->setMaximum(ui->spinY1->value()-1);
}

void uxROIWidget::setROI(int *roi)
{
    setROI(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::setROI(QRect rect)
{
    setROI(rect.x(),rect.y(),rect.x()+rect.width(),rect.y()+rect.width());
}

void uxROIWidget::getROI(QRect &rect)
{
    rect=QRect(ui->spinX0->value(),
               ui->spinY0->value(),
               ui->spinX1->value()-ui->spinX0->value(),
               ui->spinY1->value()-ui->spinY0->value());

}

void uxROIWidget::getROI(int &x0, int &y0, int &x1, int &y1)
{
    x0=ui->spinX0->value();
    y0=ui->spinY0->value();
    x1=ui->spinX1->value();
    y1=ui->spinY1->value();
}

void uxROIWidget::getROI(int *roi)
{
    getROI(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::setTitle(const QString &lbl)
{
    ui->groupROI->setTitle(lbl);
}

void uxROIWidget::on_spinX0_valueChanged(int arg1)
{
    ui->spinX1->setMinimum(arg1+1);
    int roi[4];
    getROI(roi);
    emit valueChanged(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::on_spinY0_valueChanged(int arg1)
{
    ui->spinY1->setMinimum(arg1+1);
    int roi[4];
    getROI(roi);
    emit valueChanged(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::on_spinY1_valueChanged(int arg1)
{
    ui->spinY0->setMaximum(arg1-1);
    int roi[4];
    getROI(roi);
    emit valueChanged(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::on_spinX1_valueChanged(int arg1)
{
    ui->spinX0->setMaximum(arg1-1);
    int roi[4];
    getROI(roi);
    emit valueChanged(roi[0],roi[1],roi[2],roi[3]);
}

void uxROIWidget::on_buttonGetROI_clicked()
{
    emit getROIClicked();
}
