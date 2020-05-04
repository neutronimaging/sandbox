#include "volumedisplaywidget.h"
#include "ui_volumedisplaywidget.h"
#include <QMessageBox>

#include <base/KiplException.h>

VolumeDisplayWidget::VolumeDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeDisplayWidget),
    m_graph(new QtDataVisualization::Q3DScatter())
{
    ui->setupUi(this);

    QWidget *container = QWidget::createWindowContainer(m_graph);

    if (!m_graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        throw kipl::base::KiplException("Failed to open 3D graphics view");
    }

    ui->gridLayout->addWidget(container,0,0);
}

VolumeDisplayWidget::~VolumeDisplayWidget()
{
    delete ui;
}
