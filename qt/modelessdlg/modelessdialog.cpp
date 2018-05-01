#include "modelessdialog.h"
#include "ui_modelessdialog.h"

ModeLessDialog::ModeLessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeLessDialog)
{
    ui->setupUi(this);
}

ModeLessDialog::~ModeLessDialog()
{
    delete ui;
}

void ModeLessDialog::on_lineEdit_returnPressed()
{
    qDebug("Enter pressed");
    emit TextChanged(ui->lineEdit->text());
}
