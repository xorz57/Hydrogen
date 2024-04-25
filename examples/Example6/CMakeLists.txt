add_executable(Example6 src/Main.cpp)

target_include_directories(Example6 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example6 PRIVATE glad::glad)
target_link_libraries(Example6 PRIVATE glfw)
target_link_libraries(Example6 PRIVATE glm::glm)
target_link_libraries(Example6 PRIVATE imgui::imgui)

add_custom_target(CopyAssets6 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(Example6 CopyAssets6)
