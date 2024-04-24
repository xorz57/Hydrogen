add_executable(Example1 src/Main.cpp)

target_include_directories(Example1 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example1 PRIVATE glad::glad)
target_link_libraries(Example1 PRIVATE glfw)
target_link_libraries(Example1 PRIVATE glm::glm)
target_link_libraries(Example1 PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Example1 CopyAssets)
