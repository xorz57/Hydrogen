add_executable(Example15 src/Main.cpp
                         src/Camera.cpp
                         src/Cube.cpp
                         src/Plane.cpp
                         src/Shader.cpp
                         src/Texture.cpp
                         src/EBO.cpp
                         src/VAO.cpp
                         src/VBO.cpp)

target_include_directories(Example15 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example15 PRIVATE glad::glad)
target_link_libraries(Example15 PRIVATE glfw)
target_link_libraries(Example15 PRIVATE glm::glm)
target_link_libraries(Example15 PRIVATE imgui::imgui)

add_custom_target(Example15Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example15 Example15Assets)
