add_executable(Example2 src/Main.cpp)

target_include_directories(Example2 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example2 PRIVATE glad::glad)
target_link_libraries(Example2 PRIVATE glfw)
target_link_libraries(Example2 PRIVATE glm::glm)
target_link_libraries(Example2 PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Example2 CopyAssets)
