#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logger("MainWindow"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    kipl::logging::Logger::AddLogTarget(*(ui->logviewer));
    logger(kipl::logging::Logger::LogMessage,"Enter c'tor");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonMessage_clicked()
{
    logger(logger.LogMessage,"Message");
}

void MainWindow::on_buttonDialog_clicked()
{
    ReconDialog dlg(&interactor,this);

    int res=dlg.exec(false);

    if (res==QDialog::Accepted)
        logger(logger.LogMessage,"Dialog Accecpted");
    else
        logger(logger.LogMessage,"Dialog Cancel");


}
