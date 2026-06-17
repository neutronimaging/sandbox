#include "VolumeRenderWidget.h"

#include <QFile>
#include <QMouseEvent>
#include <QVector3D>

#include <algorithm>
#include <stdexcept>

VolumeRenderWidget::VolumeRenderWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setMinimumSize(500, 500);
}

VolumeRenderWidget::~VolumeRenderWidget()
{
    makeCurrent();

    if (m_volumeTex != 0)
        glDeleteTextures(1, &m_volumeTex);

    if (m_vbo != 0)
        glDeleteBuffers(1, &m_vbo);

    if (m_vao != 0)
        glDeleteVertexArrays(1, &m_vao);

    doneCurrent();
}

void VolumeRenderWidget::setVolume(const float* data, const std::vector<size_t>& dims)
{
    if (data == nullptr)
        throw std::runtime_error("Volume data pointer is null.");

    if (dims.size() != 3)
        throw std::runtime_error("Volume dimensions must have size 3: {nx, ny, nz}.");

    const size_t nx = dims[0];
    const size_t ny = dims[1];
    const size_t nz = dims[2];

    if (nx == 0 || ny == 0 || nz == 0)
        throw std::runtime_error("Volume dimensions must be non-zero.");

    const size_t n = nx * ny * nz;
    m_volume.assign(data, data + n);
    m_dims = dims;

    const auto [minIt, maxIt] = std::minmax_element(m_volume.begin(), m_volume.end());
    m_grayMin = *minIt;
    m_grayMax = *maxIt;

    m_pendingUpload = true;
    update();
}

void VolumeRenderWidget::setOpacity(float opacity)
{
    m_opacity = std::clamp(opacity, 0.0f, 1.0f);
    update();
}

void VolumeRenderWidget::setGrayInterval(float minValue, float maxValue)
{
    m_grayMin = minValue;
    m_grayMax = std::max(maxValue, minValue + 1e-20f);
    update();
}

void VolumeRenderWidget::setRayMarchingSteps(int steps)
{
    m_steps = std::clamp(steps, 32, 2048);
    update();
}

void VolumeRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    const auto vertexSource = readResourceText(":/shaders/shaders/volume.vert");
    const auto fragmentSource = readResourceText(":/shaders/shaders/volume.frag");

    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource))
        throw std::runtime_error(m_program.log().toStdString());

    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource))
        throw std::runtime_error(m_program.log().toStdString());

    if (!m_program.link())
        throw std::runtime_error(m_program.log().toStdString());

    createCube();
    glGenTextures(1, &m_volumeTex);

    if (!m_volume.empty())
        uploadVolume();
}

void VolumeRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / float(std::max(1, h)), 0.01f, 100.0f);
}

void VolumeRenderWidget::paintGL()
{
    glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_pendingUpload && !m_volume.empty())
        uploadVolume();

    if (m_volume.empty())
        return;

    updateMatrices();

    const QMatrix4x4 mvp = m_projection * m_view * m_model;
    const QMatrix4x4 invModel = m_model.inverted();

    const QVector3D cameraWorld(0.0f, 0.0f, 2.2f);
    const QVector3D cameraLocal = invModel.map(cameraWorld);

    m_program.bind();
    m_program.setUniformValue("uMVP", mvp);
    m_program.setUniformValue("uCameraLocal", cameraLocal);
    m_program.setUniformValue("uOpacity", m_opacity);
    m_program.setUniformValue("uGrayMin", m_grayMin);
    m_program.setUniformValue("uGrayMax", m_grayMax);
    m_program.setUniformValue("uSteps", m_steps);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, m_volumeTex);
    m_program.setUniformValue("uVolume", 0);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    m_program.release();
}

void VolumeRenderWidget::mousePressEvent(QMouseEvent* event)
{
    m_lastMouse = event->pos();
}

void VolumeRenderWidget::mouseMoveEvent(QMouseEvent* event)
{
    const QPoint delta = event->pos() - m_lastMouse;
    m_lastMouse = event->pos();

    if (event->buttons() & Qt::LeftButton) {
        m_rotX += 0.5f * float(delta.y());
        m_rotY += 0.5f * float(delta.x());
        update();
    }
}

void VolumeRenderWidget::createCube()
{
    constexpr float vertices[] = {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void VolumeRenderWidget::uploadVolume()
{
    glBindTexture(GL_TEXTURE_3D, m_volumeTex);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage3D(
        GL_TEXTURE_3D,
        0,
        GL_R32F,
        static_cast<GLsizei>(m_dims[0]),
        static_cast<GLsizei>(m_dims[1]),
        static_cast<GLsizei>(m_dims[2]),
        0,
        GL_RED,
        GL_FLOAT,
        m_volume.data()
    );

    m_pendingUpload = false;
}

void VolumeRenderWidget::updateMatrices()
{
    m_view.setToIdentity();
    m_view.translate(0.0f, 0.0f, -2.2f);

    m_model.setToIdentity();
    m_model.rotate(m_rotX, 1.0f, 0.0f, 0.0f);
    m_model.rotate(m_rotY, 0.0f, 1.0f, 0.0f);
}

QByteArray VolumeRenderWidget::readResourceText(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(("Could not open resource: " + path).toStdString());

    return file.readAll();
}
