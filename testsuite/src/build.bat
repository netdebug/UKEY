@ECHO ON
set CMAKE_GENERATOR=Visual Studio 14 2015 Win64
RMDIR /Q /S build
MKDIR build
PUSHD build

conan install ..
cmake .. -G "%CMAKE_GENERATOR%"
cmake --build . --config Release
