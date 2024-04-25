add_executable(Example2 src/Main.cpp)

target_include_directories(Example2 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example2 PRIVATE glad::glad)
target_link_libraries(Example2 PRIVATE glfw)
target_link_libraries(Example2 PRIVATE glm::glm)
target_link_libraries(Example2 PRIVATE imgui::imgui)
