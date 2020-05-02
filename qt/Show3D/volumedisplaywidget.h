#ifndef VOLUMEDISPLAYWIDGET_H
#define VOLUMEDISPLAYWIDGET_H

#include <QWidget>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qcustom3dvolume.h>

namespace Ui {
class VolumeDisplayWidget;
}

class VolumeDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeDisplayWidget(QWidget *parent = nullptr);
    ~VolumeDisplayWidget();

private:
    Ui::VolumeDisplayWidget *ui;
    QtDataVisualization::Q3DScatter *m_graph;

};

#endif // VOLUMEDISPLAYWIDGET_H
