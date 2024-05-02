add_executable(Example14 src/Main.cpp
                         src/Shader.cpp
                         src/EBO.cpp
                         src/VAO.cpp
                         src/VBO.cpp)

target_include_directories(Example14 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example14 PRIVATE glad::glad)
target_link_libraries(Example14 PRIVATE glfw)
target_link_libraries(Example14 PRIVATE glm::glm)
target_link_libraries(Example14 PRIVATE imgui::imgui)

add_custom_target(Example14Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example14 Example14Assets)
