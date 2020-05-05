#ifndef VOLUMEDISPLAYWIDGET_H
#define VOLUMEDISPLAYWIDGET_H

#include <QWidget>
#include <QVector>
#include <QRgb>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qcustom3dvolume.h>

#include <base/timage.h>

namespace Ui {
class VolumeDisplayWidget;
}

class VolumeDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeDisplayWidget(QWidget *parent = nullptr);
    ~VolumeDisplayWidget();

    void setVolume(kipl::base::TImage<float, 3> &img);


private:
    void initializeViewer();
    void prepareVolumeViewer();
    void prepareVolumeData();
    Ui::VolumeDisplayWidget *ui;
    QtDataVisualization::Q3DScatter *m_graph;
    QtDataVisualization::QCustom3DVolume *m_volumeItem;
    int m_colorTableSize;
    QVector<QRgb> m_colorTable;

    kipl::base::TImage<float,3> m_volumeImage;
    QVector<uchar> m_volumeData;
};

#endif // VOLUMEDISPLAYWIDGET_H
