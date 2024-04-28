add_executable(Example04 src/Main.cpp)

target_include_directories(Example04 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example04 PRIVATE glad::glad)
target_link_libraries(Example04 PRIVATE glfw)
target_link_libraries(Example04 PRIVATE glm::glm)
target_link_libraries(Example04 PRIVATE imgui::imgui)
