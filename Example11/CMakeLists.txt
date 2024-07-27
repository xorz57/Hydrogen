add_executable(Example11 src/Main.cpp src/Shader.cpp)

target_include_directories(Example11 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example11 PRIVATE glad::glad)
target_link_libraries(Example11 PRIVATE glfw)
target_link_libraries(Example11 PRIVATE glm::glm)
target_link_libraries(Example11 PRIVATE imgui::imgui)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_target(Example11Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets)
else()
    add_custom_target(Example11Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()
add_dependencies(Example11 Example11Assets)
