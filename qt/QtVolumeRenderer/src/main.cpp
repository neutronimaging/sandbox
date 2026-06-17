#include "VolumeViewerWidget.h"

#include <QApplication>
#include <QSurfaceFormat>

#include <cmath>
#include <cstddef>
#include <vector>

namespace {

std::vector<float> makeDemoVolume(size_t nx, size_t ny, size_t nz)
{
    std::vector<float> volume(nx * ny * nz, 0.0f);

    for (size_t z = 0; z < nz; ++z) {
        for (size_t y = 0; y < ny; ++y) {
            for (size_t x = 0; x < nx; ++x) {
                const float fx = (float(x) / float(nx - 1)) * 2.0f - 1.0f;
                const float fy = (float(y) / float(ny - 1)) * 2.0f - 1.0f;
                const float fz = (float(z) / float(nz - 1)) * 2.0f - 1.0f;

                const float r0 = std::sqrt(fx * fx + fy * fy + fz * fz);
                const float r1 = std::sqrt((fx - 0.35f) * (fx - 0.35f) +
                                           (fy + 0.10f) * (fy + 0.10f) +
                                           (fz - 0.15f) * (fz - 0.15f));

                float v = 0.0f;
                v += std::exp(-8.0f * r0 * r0);
                v += 0.7f * std::exp(-80.0f * r1 * r1);

                if (std::abs(fx) < 0.05f && std::abs(fy) < 0.05f)
                    v += 0.4f;

                volume[x + nx * (y + ny * z)] = v;
            }
        }
    }

    return volume;
}

} // namespace

int main(int argc, char** argv)
{
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    fmt.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication app(argc, argv);

    constexpr size_t nx = 128;
    constexpr size_t ny = 128;
    constexpr size_t nz = 128;

    auto volume = makeDemoVolume(nx, ny, nz);

    VolumeViewerWidget viewer;
    viewer.resize(900, 800);
    viewer.setWindowTitle("Qt 6.8 OpenGL volume renderer");
    viewer.setVolume(volume.data(), {nx, ny, nz});
    viewer.show();

    return app.exec();
}
