#pragma once

#include <QWidget>
#include <cstddef>
#include <vector>

class VolumeRenderWidget;
class QDoubleSpinBox;
class QSpinBox;

class VolumeViewerWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeViewerWidget(QWidget* parent = nullptr);

    void setVolume(const float* data, const std::vector<size_t>& dims);

private:
    VolumeRenderWidget* m_renderer = nullptr;

    QDoubleSpinBox* m_opacity = nullptr;
    QDoubleSpinBox* m_grayMin = nullptr;
    QDoubleSpinBox* m_grayMax = nullptr;
    QSpinBox* m_steps = nullptr;
};
