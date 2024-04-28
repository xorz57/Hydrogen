add_executable(Example01 src/Main.cpp)

target_include_directories(Example01 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example01 PRIVATE glad::glad)
target_link_libraries(Example01 PRIVATE glfw)
target_link_libraries(Example01 PRIVATE glm::glm)
target_link_libraries(Example01 PRIVATE imgui::imgui)
