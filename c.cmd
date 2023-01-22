rmdir /s/q _b
mkdir _b
cmake -S . -B _b -DCMAKE_TOOLCHAIN_FILE=.\vcpkg\scripts\buildsystems\vcpkg.cmake
