add_executable(Example4 src/Main.cpp)

target_include_directories(Example4 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example4 PRIVATE glad::glad)
target_link_libraries(Example4 PRIVATE glfw)
target_link_libraries(Example4 PRIVATE glm::glm)
target_link_libraries(Example4 PRIVATE imgui::imgui)
