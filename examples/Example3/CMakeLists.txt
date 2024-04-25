add_executable(Example3 src/Main.cpp)

target_include_directories(Example3 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example3 PRIVATE glad::glad)
target_link_libraries(Example3 PRIVATE glfw)
target_link_libraries(Example3 PRIVATE glm::glm)
target_link_libraries(Example3 PRIVATE imgui::imgui)
