# QtVolumeRendererPixi

A small Qt 6.8 / C++22 OpenGL volume-rendering widget packaged for Pixi.

The renderer accepts a contiguous `float` volume and dimensions in the order:

```cpp
std::vector<size_t> dims = {nx, ny, nz};
index = x + nx * (y + ny * z);
```

Features:

- `QOpenGLWidget`-based GPU ray marching
- `GL_R32F` 3D texture input
- Mouse rotation with the left mouse button
- Opacity control
- Gray-level min/max interval control
- Ray-marching step control
- GLSL shaders stored as Qt resources

## Build with Pixi

```bash
pixi install
pixi run build
pixi run run
```

or explicitly:

```bash
pixi run configure
pixi run build
pixi run run
```

## Manual CMake build

```bash
cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/QtVolumeRenderer
```

## Using the widget

```cpp
VolumeViewerWidget viewer;
viewer.setVolume(volume.data(), {nx, ny, nz});
viewer.show();
```

For direct embedding without the controls, use `VolumeRenderWidget`.

## Notes

This is a compact scientific visualization starting point, not a complete production volume renderer. Useful next additions would be:

- anisotropic voxel spacing
- color transfer function
- clipping planes
- slicing overlays
- orthographic camera mode
- histogram-based window controls
- support for TImage adapters
