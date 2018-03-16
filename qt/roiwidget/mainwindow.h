#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void getROIclicked();
    void on_valueChanged(int x0,int y0, int x1, int y1);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int cnt;
};

#endif // MAINWINDOW_H
