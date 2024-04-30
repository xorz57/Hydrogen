add_executable(Example13 src/Main.cpp src/Shader.cpp)

target_include_directories(Example13 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example13 PRIVATE glad::glad)
target_link_libraries(Example13 PRIVATE glfw)
target_link_libraries(Example13 PRIVATE glm::glm)
target_link_libraries(Example13 PRIVATE imgui::imgui)

add_custom_target(Example13Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example13 Example13Assets)
