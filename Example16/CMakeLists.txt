add_executable(Example16 src/Main.cpp
                         src/Camera.cpp
                         src/Cube.cpp
                         src/Plane.cpp
                         src/Quad.cpp
                         src/Shader.cpp
                         src/Texture.cpp
                         src/VAO.cpp)

target_include_directories(Example16 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example16 PRIVATE glad::glad)
target_link_libraries(Example16 PRIVATE glfw)
target_link_libraries(Example16 PRIVATE glm::glm)
target_link_libraries(Example16 PRIVATE imgui::imgui)

add_custom_target(Example16Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example16 Example16Assets)
