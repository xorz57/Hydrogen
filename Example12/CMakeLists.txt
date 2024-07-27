add_executable(Example12 src/Main.cpp src/Shader.cpp)

target_include_directories(Example12 PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(Example12 PRIVATE glad::glad)
target_link_libraries(Example12 PRIVATE glfw)
target_link_libraries(Example12 PRIVATE glm::glm)
target_link_libraries(Example12 PRIVATE imgui::imgui)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    add_custom_target(Example12Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets)
else()
    add_custom_target(Example12Assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
endif()
add_dependencies(Example12 Example12Assets)
