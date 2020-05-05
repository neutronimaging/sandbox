#include "volumedisplaywidget.h"
#include "ui_volumedisplaywidget.h"
#include <QMessageBox>
#include <Q3DTheme>
#include <QAbstract3DGraph>
#include <Q3DCamera>
#include <Q3DInputHandler>
#include <QCustom3DLabel>
#include <Q3DLight>

#include <base/KiplException.h>
#include <base/imageoperators.h>

static bool isOpenGLES()
{
#if defined(QT_OPENGL_ES_2)
    return true;
#elif (QT_VERSION < QT_VERSION_CHECK(5, 3, 0))
    return false;
#else
    return QOpenGLContext::currentContext()->isOpenGLES();
#endif
}

VolumeDisplayWidget::VolumeDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeDisplayWidget),
    m_graph(new QtDataVisualization::Q3DScatter()),
    m_volumeItem(nullptr),
    m_colorTableSize(256)
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

    initializeViewer();

}

VolumeDisplayWidget::~VolumeDisplayWidget()
{
    delete ui;
}

void VolumeDisplayWidget::setVolume(kipl::base::TImage<float, 3> &img)
{
    m_volumeImage = img;

    prepareVolumeData();

    prepareVolumeViewer();
}

void VolumeDisplayWidget::initializeViewer()
{
    m_graph->activeTheme()->setType(QtDataVisualization::Q3DTheme::ThemeDigia);
    m_graph->setShadowQuality(QtDataVisualization::QAbstract3DGraph::ShadowQualityHigh);
    m_graph->scene()->activeCamera()->setCameraPreset(QtDataVisualization::Q3DCamera::CameraPresetDirectlyAboveCW45);
    m_graph->scene()->setActiveLight(new QtDataVisualization::Q3DLight);
    //! [6]
    m_graph->setOrthoProjection(true);
    //! [6]
    m_graph->activeTheme()->setBackgroundEnabled(false);

    // Only allow zooming at the center and limit the zoom to 200% to avoid clipping issues
    static_cast<QtDataVisualization::Q3DInputHandler *>(m_graph->activeInputHandler())->setZoomAtTargetEnabled(false);
    m_graph->scene()->activeCamera()->setMaxZoomLevel(200.0f);
}

void VolumeDisplayWidget::prepareVolumeViewer()
{
    if (!isOpenGLES()) {

        //! [0]
        m_volumeItem = new QtDataVisualization::QCustom3DVolume;
        // Adjust water level to zero with a minor tweak to y-coordinate position and scaling
        m_volumeItem->setScaling(
                    QVector3D(m_graph->axisX()->max() - m_graph->axisX()->min(),
                              (m_graph->axisY()->max() - m_graph->axisY()->min()),
                              m_graph->axisZ()->max() - m_graph->axisZ()->min()));
        m_volumeItem->setPosition(
                    QVector3D((m_graph->axisX()->max() + m_graph->axisX()->min()) / 2.0f,
                              -0.045f * (m_graph->axisY()->max() - m_graph->axisY()->min()) +
                              (m_graph->axisY()->max() + m_graph->axisY()->min()) / 2.0f,
                              (m_graph->axisZ()->max() + m_graph->axisZ()->min()) / 2.0f));
        m_volumeItem->setScalingAbsolute(false);
        //! [0]
        //! [1]

        qDebug() <<m_volumeImage.Size(0)<<m_volumeImage.Size(1)<<m_volumeImage.Size(2);
        int rest=m_volumeImage.Size(0) % 4 ;

        m_volumeItem->setTextureWidth(m_volumeImage.Size(0) + (rest ? 4-rest : 0));
        m_volumeItem->setTextureHeight(m_volumeImage.Size(2));
        m_volumeItem->setTextureDepth(m_volumeImage.Size(1));
        m_volumeItem->setTextureFormat(QImage::Format_Indexed8);
        m_volumeItem->setTextureData(new QVector<uchar>(m_volumeData));
        //! [1]

//        // Generate color tables.
        m_colorTable.resize(m_colorTableSize);

        for (int idx=0; idx<m_colorTableSize; ++idx)
        {
            m_colorTable[idx] = qRgba(idx,idx,idx,idx); // R,G,B,A
        }

        m_volumeItem->setColorTable(m_colorTable);
//        //! [2]

//        //! [5]
        m_volumeItem->setSliceFrameGaps(QVector3D(1.0f,1.0f,1.0f));
        m_volumeItem->setSliceFrameThicknesses(QVector3D(1.0f, 1.0f, 1.0f));
        m_volumeItem->setSliceFrameWidths(QVector3D(1.0f, 1.0f, 1.0f));
        m_volumeItem->setDrawSliceFrames(true);
//        //! [5]
//        handleSlicingChanges();

        //! [3]
        m_graph->addCustomItem(m_volumeItem);
        //! [3]

//        m_timer.start(0);
    } else {
        // OpenGL ES2 doesn't support 3D textures, so show a warning label instead
        QtDataVisualization::QCustom3DLabel *warningLabel = new QtDataVisualization::QCustom3DLabel(
                    "QCustom3DVolume is not supported with OpenGL ES2",
                    QFont(),
                    QVector3D(0.0f, 0.5f, 0.0f),
                    QVector3D(1.5f, 1.5f, 0.0f),
                    QQuaternion());
        warningLabel->setPositionAbsolute(true);
        warningLabel->setFacingCamera(true);
        m_graph->addCustomItem(warningLabel);
    }
}

void VolumeDisplayWidget::prepareVolumeData()
{
    int xLineRest = (4 - m_volumeImage.Size(0) % 4) % 4;
    int xLineSize = m_volumeImage.Size(0) + xLineRest;
    int textureSize = static_cast<uint>(xLineSize * m_volumeImage.Size(1) * m_volumeImage.Size(2) );

    m_volumeData.resize(textureSize);

    float imgMin=kipl::base::min(m_volumeImage);
    float imgMax=kipl::base::max(m_volumeImage);

    for (int idx = 0, z=0; z < m_volumeImage.Size(2); ++z)
        for (int y = 0; y < m_volumeImage.Size(1); ++y)
        {
            for (int x = 0; x < m_volumeImage.Size(0); ++x, ++idx)
            {
                 // Generate layer height arrays
                 unsigned char colorIndex = static_cast<uchar>((m_volumeImage[idx]-imgMin)/(imgMax-imgMin)*255.0f);
                 m_volumeData[idx] = colorIndex;
            }

            for (int rest = 0; rest < xLineRest; ++rest, ++idx)
                m_volumeData[idx]=0;
        }
}
