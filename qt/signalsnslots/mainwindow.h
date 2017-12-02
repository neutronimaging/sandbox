#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <logging/logger.h>
#include <interactors/interactionbase.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    kipl::logging::Logger logger;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonMessage_clicked();

    void on_buttonDialog_clicked();

private:
    Ui::MainWindow *ui;
    kipl::interactors::InteractionBase interactor;
};

#endif // MAINWINDOW_H
