add_executable(Example9 src/Main.cpp src/Mesh.cpp src/Shader.cpp)

target_include_directories(Example9 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example9 PRIVATE glad::glad)
target_link_libraries(Example9 PRIVATE glfw)
target_link_libraries(Example9 PRIVATE glm::glm)
target_link_libraries(Example9 PRIVATE imgui::imgui)

add_custom_target(Example9Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example9 Example9Assets)
