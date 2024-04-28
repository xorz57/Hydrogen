add_executable(Example08 src/Main.cpp src/Shader.cpp)

target_include_directories(Example08 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example08 PRIVATE glad::glad)
target_link_libraries(Example08 PRIVATE glfw)
target_link_libraries(Example08 PRIVATE glm::glm)
target_link_libraries(Example08 PRIVATE imgui::imgui)

add_custom_target(Example08Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example08 Example08Assets)
