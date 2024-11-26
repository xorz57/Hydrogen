# OpenGLSandbox

![example16a](https://github.com/xorz57/OpenGLSandbox/assets/84932056/e279efc0-45dd-48cd-a4a3-4b3c2e8683d8)

![example16b](https://github.com/xorz57/OpenGLSandbox/assets/84932056/0c3af01f-5b85-4b7a-8bcb-9a5846b614e4)

## Dependencies

OpenGLSandbox relies on the following libraries:

- [glad](https://github.com/Dav1dde/glad)
- [glfw3](https://github.com/glfw/glfw)
- [glm](https://github.com/g-truc/glm)
- [imgui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)
- [spdlog](https://github.com/gabime/spdlog)

## How to Build

#### Linux & macOS

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh

git clone https://github.com/xorz57/OpenGLSandbox.git
cd OpenGLSandbox
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --test-dir build --build-config Release
```

#### Windows

```powershell
git clone https://github.com/microsoft/vcpkg.git C:/vcpkg
C:/vcpkg/bootstrap-vcpkg.bat
C:/vcpkg/vcpkg.exe integrate install

git clone https://github.com/xorz57/OpenGLSandbox.git
cd OpenGLSandbox
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --test-dir build --build-config Release
```
