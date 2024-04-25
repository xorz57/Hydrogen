add_executable(Example5 src/Main.cpp)

target_include_directories(Example5 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example5 PRIVATE glad::glad)
target_link_libraries(Example5 PRIVATE glfw)
target_link_libraries(Example5 PRIVATE glm::glm)
target_link_libraries(Example5 PRIVATE imgui::imgui)

# add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
# add_dependencies(Example5 CopyAssets)
