add_executable(Example02 src/Main.cpp)

target_include_directories(Example02 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example02 PRIVATE glad::glad)
target_link_libraries(Example02 PRIVATE glfw)
target_link_libraries(Example02 PRIVATE glm::glm)
target_link_libraries(Example02 PRIVATE imgui::imgui)
