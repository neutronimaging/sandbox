#ifndef UXROIWIDGET_H
#define UXROIWIDGET_H

#include <QWidget>
#include <QRect>
#include <QString>

namespace Ui {
class uxROIWidget;
}

class uxROIWidget : public QWidget
{
    Q_OBJECT

public:
    explicit uxROIWidget(QWidget *parent = 0);
    ~uxROIWidget();

    void setROI(int x0, int y0, int x1, int y1);
    void setROI(int *roi);
    void setROI(QRect rect);
    void setBoundingBox(int x0, int y0, int x1, int y1, bool updateFields=false);

    void getROI(QRect &rect);
    void getROI(int &x0, int &y0, int &x1, int &y1);
    void getROI(int *roi);

    void setTitle(const QString &lbl);
    bool setROIColor(const QString color);

private slots:
    void on_spinX0_valueChanged(int arg1);

    void on_spinY0_valueChanged(int arg1);

    void on_spinY1_valueChanged(int arg1);

    void on_spinX1_valueChanged(int arg1);

    void on_buttonGetROI_clicked();

private:
    Ui::uxROIWidget *ui;

signals:
    void getROIClicked(void);
    void valueChanged(int x0,int y0, int x1, int y1);
};

#endif // UXROIWIDGET_H
