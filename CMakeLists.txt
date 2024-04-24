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

add_executable(Example1 examples/Example1.cpp)

target_include_directories(Example1 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example1 PRIVATE glad::glad)
target_link_libraries(Example1 PRIVATE glfw)
target_link_libraries(Example1 PRIVATE glm::glm)
target_link_libraries(Example1 PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Example1 CopyAssets)

add_executable(Example2 examples/Example2.cpp)

target_include_directories(Example2 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example2 PRIVATE glad::glad)
target_link_libraries(Example2 PRIVATE glfw)
target_link_libraries(Example2 PRIVATE glm::glm)
target_link_libraries(Example2 PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Example2 CopyAssets)
