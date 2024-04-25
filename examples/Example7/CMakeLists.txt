add_executable(Example7 src/Main.cpp)

target_include_directories(Example7 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example7 PRIVATE glad::glad)
target_link_libraries(Example7 PRIVATE glfw)
target_link_libraries(Example7 PRIVATE glm::glm)
target_link_libraries(Example7 PRIVATE imgui::imgui)

add_custom_target(CopyAssets7 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example7 CopyAssets7)
