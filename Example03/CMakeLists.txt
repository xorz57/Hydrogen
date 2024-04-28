add_executable(Example03 src/Main.cpp)

target_include_directories(Example03 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example03 PRIVATE glad::glad)
target_link_libraries(Example03 PRIVATE glfw)
target_link_libraries(Example03 PRIVATE glm::glm)
target_link_libraries(Example03 PRIVATE imgui::imgui)
