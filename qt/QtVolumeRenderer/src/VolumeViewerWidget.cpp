#include "VolumeViewerWidget.h"
#include "VolumeRenderWidget.h"

#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>

VolumeViewerWidget::VolumeViewerWidget(QWidget* parent)
    : QWidget(parent)
{
    m_renderer = new VolumeRenderWidget(this);

    m_opacity = new QDoubleSpinBox(this);
    m_opacity->setRange(0.0, 1.0);
    m_opacity->setSingleStep(0.01);
    m_opacity->setValue(0.08);

    m_grayMin = new QDoubleSpinBox(this);
    m_grayMin->setRange(-1e9, 1e9);
    m_grayMin->setDecimals(6);

    m_grayMax = new QDoubleSpinBox(this);
    m_grayMax->setRange(-1e9, 1e9);
    m_grayMax->setDecimals(6);
    m_grayMax->setValue(1.0);

    m_steps = new QSpinBox(this);
    m_steps->setRange(32, 2048);
    m_steps->setSingleStep(32);
    m_steps->setValue(384);

    auto* controls = new QFormLayout;
    controls->addRow("Opacity", m_opacity);
    controls->addRow("Gray min", m_grayMin);
    controls->addRow("Gray max", m_grayMax);
    controls->addRow("Ray steps", m_steps);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_renderer, 1);
    layout->addLayout(controls);

    connect(m_opacity, &QDoubleSpinBox::valueChanged, this, [this](double v) {
        m_renderer->setOpacity(static_cast<float>(v));
    });

    connect(m_grayMin, &QDoubleSpinBox::valueChanged, this, [this](double) {
        m_renderer->setGrayInterval(
            static_cast<float>(m_grayMin->value()),
            static_cast<float>(m_grayMax->value())
        );
    });

    connect(m_grayMax, &QDoubleSpinBox::valueChanged, this, [this](double) {
        m_renderer->setGrayInterval(
            static_cast<float>(m_grayMin->value()),
            static_cast<float>(m_grayMax->value())
        );
    });

    connect(m_steps, &QSpinBox::valueChanged, this, [this](int v) {
        m_renderer->setRayMarchingSteps(v);
    });
}

void VolumeViewerWidget::setVolume(const float* data, const std::vector<size_t>& dims)
{
    m_renderer->setVolume(data, dims);
}
