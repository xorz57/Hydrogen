cmake_minimum_required(VERSION 3.26)

cmake_policy(SET CMP0091 NEW)

project(Graphite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(Stb REQUIRED)

set(SOURCES src/Main.cpp)

add_executable(Graphite ${SOURCES})

target_include_directories(Graphite PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Graphite PRIVATE glad::glad)
target_link_libraries(Graphite PRIVATE glfw)
target_link_libraries(Graphite PRIVATE glm::glm)
target_link_libraries(Graphite PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Graphite CopyAssets)
