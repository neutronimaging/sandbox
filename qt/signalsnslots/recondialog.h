#ifndef RECONDIALOG_H
#define RECONDIALOG_H

#include <QDialog>

#include <logging/logger.h>
#include <interactors/interactionbase.h>

namespace Ui {
class ReconDialog;
}

class ReconDialog : public QDialog
{
    Q_OBJECT

    kipl::logging::Logger logger;

public:
    explicit ReconDialog(kipl::interactors::InteractionBase *interactor, QWidget *parent = 0);
    ~ReconDialog();
    int progress();
    int process();
    virtual int exec(bool bRerunBackProj);

signals:
    void progressChanged(int currentProgress, int overallProgress, QString message);

protected:
    Ui::ReconDialog *ui;

    virtual int exec() { return QDialog::exec(); }

    void Abort();
    bool Finished();

    float fraction;
    bool finish;

    kipl::interactors::InteractionBase * m_Interactor;
    bool m_bRerunBackproj;

private slots:
    void on_buttonCancel_clicked();
    void setProgress(int currentProgress,int overallProgress,QString message);
};

#endif // RECONDIALOG_H
