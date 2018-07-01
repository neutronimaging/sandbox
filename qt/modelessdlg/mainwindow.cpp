#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mdlg(new ModeLessDialog(this))
{
    ui->setupUi(this);
    mdlg->setModal(false);
    connect(mdlg,&ModeLessDialog::TextChanged,this,&MainWindow::onTextFromDialog);

}

MainWindow::~MainWindow()
{
    delete mdlg;
    delete ui;
}

void MainWindow::onTextFromDialog(const QString &txt)
{
    ui->label->setText(txt);

}

void MainWindow::on_pushButton_clicked()
{
    if (mdlg->isHidden()) {

        mdlg->show();
    }
    else {
        mdlg->hide();
    }
}
