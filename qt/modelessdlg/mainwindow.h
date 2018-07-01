#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modelessdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onTextFromDialog(const QString &txt);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ModeLessDialog *mdlg;
};

#endif // MAINWINDOW_H
