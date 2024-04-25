add_executable(Example1 src/Main.cpp)

target_include_directories(Example1 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example1 PRIVATE glad::glad)
target_link_libraries(Example1 PRIVATE glfw)
target_link_libraries(Example1 PRIVATE glm::glm)
target_link_libraries(Example1 PRIVATE imgui::imgui)
