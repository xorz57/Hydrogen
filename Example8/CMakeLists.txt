add_executable(Example8 src/Main.cpp src/Shader.cpp)

target_include_directories(Example8 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example8 PRIVATE glad::glad)
target_link_libraries(Example8 PRIVATE glfw)
target_link_libraries(Example8 PRIVATE glm::glm)
target_link_libraries(Example8 PRIVATE imgui::imgui)

add_custom_target(Example8Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example8 Example8Assets)
