#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineSeries>
#include <QPointF>
#include <QAreaSeries>
#include <QPen>
#include <QLinearGradient>
#include <QChart>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QMarginsF>
#endif
#include <QSvgGenerator>
#include <QPdfWriter>
#include <QTextStream>

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

void MainWindow::on_pushButton_4_clicked()
{
    //ui->widget->grab();

    QPdfWriter writer("/Users/kaestner/out.pdf");
    writer.setPageSize(QPagedPaintDevice::A4);

    QPainter painter(&writer);

    ui->widget->render(&painter);

    painter.end();
}

void MainWindow::on_pushButton_5_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(QMarginsF(25.0,25.0,25.0,25.0));

    QString svgfname=QDir::homePath()+"/figtemp.svg";
    QSvgGenerator generator;
 //   generator.setFileName(svgfname);
    generator.setSize(QSize(1024, 1024));
    generator.setViewBox(QRect(0, 0, 1024, 1024));
    generator.setTitle(tr("SVG Generator Example Drawing"));

    QPainter painter(&generator);
    painter.begin(&generator);
    ui->widget->render(&painter);
    painter.end();


    QTextDocument doc;
    QTextCursor cursor(&doc);
   doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p><h2>The plot</h2><br/> <img src=\"/Users/kaestner/test.svg\" width=\"256\" alt=\"Kiwi standing on oval\" />");
    cursor.insertHtml("<br/>");
    doc.drawContents(&painter);
    cursor.insertHtml("<br/>");
    cursor.insertHtml("<p>test</p>");

    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

}
