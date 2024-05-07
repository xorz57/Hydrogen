#include "Camera.hpp"
#include "Cube.hpp"
#include "Plane.hpp"
#include "Shader.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cinttypes>
#include <cstdlib>
#include <iostream>
#include <vector>

static void glfw_error_callback(int error, const char *description) {
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Example16", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    std::clog << "OpenGL Vendor: " << (const GLchar *) glGetString(GL_VENDOR) << std::endl;
    std::clog << "OpenGL Renderer: " << (const GLchar *) glGetString(GL_RENDERER) << std::endl;
    std::clog << "OpenGL Version: " << (const GLchar *) glGetString(GL_VERSION) << std::endl;
    std::clog << "OpenGL Shading Language Version: " << (const GLchar *) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ///////////////////////////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);

    const std::vector<glm::vec3> positions = {
            glm::vec3(-4.0f, +4.0f, -4.0f),// 0
            glm::vec3(-4.0f, +4.0f, +0.0f),// 1
            glm::vec3(-4.0f, +4.0f, +4.0f),// 2
            glm::vec3(+0.0f, +4.0f, -4.0f),// 3
            glm::vec3(+0.0f, +4.0f, +0.0f),// 4
            glm::vec3(+0.0f, +4.0f, +4.0f),// 5
            glm::vec3(+4.0f, +4.0f, -4.0f),// 6
            glm::vec3(+4.0f, +4.0f, +0.0f),// 7
            glm::vec3(+4.0f, +4.0f, +4.0f),// 8
    };

    Plane plane;
    Cube cube;

    Shader shader = Shader::LoadFromFile("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");

    CameraSettings settings;
    settings.position = glm::vec3(+0.0f, +8.0f, +8.0f);
    settings.pitch = 45.0f;
    settings.yaw = -90.0f;

    Camera camera(settings);

    ///////////////////////////////////////////////////////////////////////////

    std::uint64_t frame = 0;
    double t0 = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        ++frame;
        const double t1 = glfwGetTime();
        const double dt = t1 - t0;
        t0 = t1;

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Statistics");
        ImGui::Text("frame: %" PRIu64, frame);
        ImGui::Text("dt: %.5lf sec", dt);
        ImGui::End();

        ImGui::Begin("Camera");
        ImGui::InputFloat3("Position", glm::value_ptr(settings.position));
        ImGui::InputFloat("FOV", &settings.fov);
        ImGui::InputFloat("Near", &settings.near);
        ImGui::InputFloat("Far", &settings.far);
        ImGui::InputFloat("Pitch", &settings.pitch);
        ImGui::InputFloat("Yaw", &settings.yaw);
        ImGui::InputFloat("Sensitivity", &settings.sensitivity);
        ImGui::InputFloat("Speed", &settings.speed);
        ImGui::End();

        ImGui::Render();

        int window_w;
        int window_h;
        glfwGetFramebufferSize(window, &window_w, &window_h);
        glViewport(0, 0, window_w, window_h);

        const float window_a = static_cast<float>(window_w) / static_cast<float>(window_h);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///////////////////////////////////////////////////////////////////////

        if (!ImGui::IsAnyItemActive()) {
            camera.Move(window_w, window_h, dt);
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        shader.Use();
        shader.UploadFloat4x4("u_View", camera.GetView());
        shader.UploadFloat4x4("u_Projection", camera.GetProjection(window_a));
        shader.UploadFloat4x4("u_Model", model);

        plane.Draw();

        for (const auto position: positions) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::translate(model, position);
            model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(-45.0f), glm::vec3(1.0f, 1.0f, 1.0f));

            shader.Use();
            shader.UploadFloat4x4("u_View", camera.GetView());
            shader.UploadFloat4x4("u_Projection", camera.GetProjection(window_a));
            shader.UploadFloat4x4("u_Model", model);

            cube.Draw();
        }

        ///////////////////////////////////////////////////////////////////////

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    ///////////////////////////////////////////////////////////////////////////

    plane.Delete();
    cube.Delete();
    shader.Delete();

    ///////////////////////////////////////////////////////////////////////////

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
