#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineSeries>
#include <QPointF>
#include <QAreaSeries>
#include <QPen>
#include <QLinearGradient>
#include <QChart>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();

    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
            << QPointF(16, 7) << QPointF(18, 5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
            << QPointF(16, 4) << QPointF(18, 3);

    QChart *chart = new QChart();

    chart->addSeries(series0);
    chart->addSeries(series1);

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 20);
    chart->axisY()->setRange(0, 10);
    chart->legend()->hide();

    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_pushButton_2_clicked()
{
    QLineSeries *series0 = new QLineSeries();
    QLineSeries *series1 = new QLineSeries();

    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
            << QPointF(16, 7) << QPointF(18, 5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
            << QPointF(16, 4) << QPointF(18, 3);

    QAreaSeries *series = new QAreaSeries(series0, series1);

    series->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple areachart example");
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 20);
    chart->axisY()->setRange(0, 10);

    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_pushButton_3_clicked()
{
    QBoxPlotSeries *insetSeries = new QBoxPlotSeries();

    QBoxSet *set0 = new QBoxSet("hepp");

    set0->setValue(QBoxSet::LowerExtreme,-10.0);
    set0->setValue(QBoxSet::UpperExtreme,15.0);
    set0->setValue(QBoxSet::LowerQuartile,-2);
    set0->setValue(QBoxSet::UpperQuartile,3);
    set0->setValue(QBoxSet::Median,0);
    insetSeries->append(set0);


    QChart *chart = new QChart(); // Life time

    chart->addSeries(insetSeries);

    chart->legend()->hide();
    chart->createDefaultAxes();

    ui->widget->setChart(chart);
}
