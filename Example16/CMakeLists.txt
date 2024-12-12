add_executable(Example16 src/Main.cpp
                         src/Application.cpp
                         src/Camera.cpp
                         src/Shapes/Capsule.cpp
                         src/Shapes/Circle.cpp
                         src/Shapes/Cube.cpp
                         src/Shapes/Cylinder.cpp
                         src/Shapes/Plane.cpp
                         src/Shapes/Quad.cpp
                         src/Shapes/Sphere.cpp
                         src/Shapes/Triangle.cpp
                         src/Logging.cpp
                         src/Shader.cpp
                         src/Texture.cpp
                         src/VAO.cpp)

target_include_directories(Example16 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example16 PRIVATE assimp::assimp)
target_link_libraries(Example16 PRIVATE glad::glad)
target_link_libraries(Example16 PRIVATE glfw)
target_link_libraries(Example16 PRIVATE glm::glm)
target_link_libraries(Example16 PRIVATE imgui::imgui)
target_link_libraries(Example16 PRIVATE spdlog::spdlog)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_target(Example16Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets)
else()
    add_custom_target(Example16Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()
add_dependencies(Example16 Example16Assets)
