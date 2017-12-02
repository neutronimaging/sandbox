//<LICENSE>

#include <QMessageBox>
#include <QtConcurrent>
#include <QFuture>
#include "recondialog.h"
#include "ui_recondialog.h"


#include <iostream>
#include <base/KiplException.h>

ReconDialog::ReconDialog(kipl::interactors::InteractionBase *interactor, QWidget *parent) :
    QDialog(parent),
    logger("ReconDialog"),
    ui(new Ui::ReconDialog),
    fraction(0.0f),
    finish(false),
    m_Interactor(interactor),
    m_bRerunBackproj(false)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(progressChanged(int , int , QString )),
                     this, SLOT(setProgress(int ,int ,QString )));
}

ReconDialog::~ReconDialog()
{
    delete ui;
}

int ReconDialog::exec(bool bRerunBackProj)
{
    m_bRerunBackproj=bRerunBackProj;
    finish=false;
    logger(kipl::logging::Logger::LogMessage,"Start");

    m_Interactor->Reset();

    logger(logger.LogMessage,"Starting with threads");
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);

    QFuture<int> proc_thread=QtConcurrent::run(this,&ReconDialog::process);
    QFuture<int> progress_thread=QtConcurrent::run(this,&ReconDialog::progress);

    int res=exec();

    finish=true;
    if (res==QDialog::Rejected) {
        std::cout<<"calling abort process"<<std::endl;
        logger(kipl::logging::Logger::LogVerbose,"Cancel requested by user");
        Abort();
    }

    proc_thread.waitForFinished();
    progress_thread.waitForFinished();
    logger(kipl::logging::Logger::LogVerbose,"Threads are joined");
    return res;
}

int ReconDialog::progress()
{
    logger(kipl::logging::Logger::LogMessage,"Progress thread is started");
    QThread::msleep(250);
    while (!m_Interactor->Finished() && !m_Interactor->Aborted() ){
        emit progressChanged(m_Interactor->CurrentProgress(),
                             m_Interactor->CurrentOverallProgress(),
                             QString::fromStdString(m_Interactor->CurrentMessage()));

        QThread::msleep(50);
    }

    logger(kipl::logging::Logger::LogMessage,"Progress thread end");

    return 0;
}

void ReconDialog::setProgress(int currentProgress,int overallProgress,QString message)
{
    ui->progressBar->setValue(currentProgress*100);
    ui->progressBar_overall->setValue(overallProgress*100);
    ui->label_message->setText(message);
}

void ReconDialog::progressChanged(int currentProgress,int overallProgress,QString message)
{
    setProgress(currentProgress,overallProgress,message);
}

int ReconDialog::process()
{
    logger(kipl::logging::Logger::LogMessage,"Process thread is started");
    std::ostringstream msg;

    for (int i=0; i<10; ++i) {
        m_Interactor->SetOverallProgress(i/10.0f);
        for (int j=0; j<10; ++j) {
            m_Interactor->SetProgress(j/10.f);
        }
    }

    logger(kipl::logging::Logger::LogMessage,"Reconstruction done");

    finish=true;
    m_Interactor->Done();
    this->accept();
    return 0;
}

void ReconDialog::Abort()
{
    if (m_Interactor!=nullptr) {
        m_Interactor->Abort();
    }
}

bool ReconDialog::Finished()
{
    if (m_Interactor!=nullptr) {
        return m_Interactor->Finished();
    }

    return true;
}


void ReconDialog::on_buttonCancel_clicked()
{
    this->reject();
}
