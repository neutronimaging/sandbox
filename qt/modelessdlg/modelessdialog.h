#ifndef MODELESSDIALOG_H
#define MODELESSDIALOG_H

#include <QDialog>

class QString;

namespace Ui {
class ModeLessDialog;
}

class ModeLessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeLessDialog(QWidget *parent = 0);
    ~ModeLessDialog();

private slots:
    void on_lineEdit_returnPressed();

private:
    Ui::ModeLessDialog *ui;

signals:
    void TextChanged(const QString &str);
};

#endif // MODELESSDIALOG_H
