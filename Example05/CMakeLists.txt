add_executable(Example05 src/Main.cpp)

target_include_directories(Example05 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example05 PRIVATE glad::glad)
target_link_libraries(Example05 PRIVATE glfw)
target_link_libraries(Example05 PRIVATE glm::glm)
target_link_libraries(Example05 PRIVATE imgui::imgui)
