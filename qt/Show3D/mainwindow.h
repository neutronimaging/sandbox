#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <base/timage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();
    
    void on_pushButtonRenderSphere_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    kipl::base::TImage<float,3> img;
};
#endif // MAINWINDOW_H
