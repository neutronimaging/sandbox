#pragma once

#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPoint>

#include <cstddef>
#include <vector>

class VolumeRenderWidget final : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit VolumeRenderWidget(QWidget* parent = nullptr);
    ~VolumeRenderWidget() override;

    void setVolume(const float* data, const std::vector<size_t>& dims);
    void setOpacity(float opacity);
    void setGrayInterval(float minValue, float maxValue);
    void setRayMarchingSteps(int steps);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void createCube();
    void uploadVolume();
    void updateMatrices();
    static QByteArray readResourceText(const QString& path);

    std::vector<float> m_volume;
    std::vector<size_t> m_dims{0, 0, 0};

    GLuint m_volumeTex = 0;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;

    QOpenGLShaderProgram m_program;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;

    QPoint m_lastMouse;
    float m_rotX = 20.0f;
    float m_rotY = -30.0f;

    float m_opacity = 0.08f;
    float m_grayMin = 0.0f;
    float m_grayMax = 1.0f;
    int m_steps = 384;

    bool m_pendingUpload = false;
};
