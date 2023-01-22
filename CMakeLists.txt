cmake_minimum_required(VERSION 3.15)

#set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#  CACHE STRING "Vcpkg toolchain file")

 set(CMAKE_TOOLCHAIN_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(wwivconfigtv CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
# Work around https://gitlab.kitware.com/cmake/cmake/-/issues/24209 util cmake 3.25.1
set (CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 0)

find_package(fmt CONFIG REQUIRED)
find_package(tvision CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
add_subdirectory(deps/tvwcommon)
add_executable(${PROJECT_NAME} 
  "src/main.cpp" 
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  fmt::fmt 
  nlohmann_json::nlohmann_json
  tvision::tvision
  tvwcommon
)

