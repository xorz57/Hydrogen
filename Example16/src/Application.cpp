#include "Application.hpp"

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

void Application::Run() {
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
    glEnable(GL_MULTISAMPLE);

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

    Camera camera;
    camera.SetPosition(glm::vec3(+0.0f, +16.0f, +16.0f));
    camera.SetFOV(45.0f);
    camera.SetNear(0.1f);
    camera.SetFar(100.0f);
    camera.SetPitch(45.0f);
    camera.SetYaw(-90.0f);
    camera.SetSensitivity(0.1f);
    camera.SetSpeed(4.0f);

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

        {
            ImGui::Begin("Statistics");
            ImGui::Text("frame: %" PRIu64, frame);
            ImGui::Text("dt: %.5lf sec", dt);
            ImGui::End();
        }

        {
            auto position = camera.GetPosition();
            float fov = camera.GetFOV();
            float near = camera.GetNear();
            float far = camera.GetFar();
            float pitch = camera.GetPitch();
            float yaw = camera.GetYaw();
            float sensitivity = camera.GetSensitivity();
            float speed = camera.GetSpeed();

            ImGui::Begin("Camera");
            ImGui::InputFloat3("Position", glm::value_ptr(position));
            ImGui::DragFloat("FOV", &fov, 1.0f, 45.0f, 120.0f);
            ImGui::InputFloat("Near", &near);
            ImGui::InputFloat("Far", &far);
            ImGui::DragFloat("Pitch", &pitch, 0.1f, -89.0f, +89.0f);
            ImGui::DragFloat("Yaw", &yaw, 0.1f, 0.0f, +360.0f);
            ImGui::DragFloat("Sensitivity", &sensitivity, 0.1f, 0.1f, 1.0f);
            ImGui::DragFloat("Speed", &speed, 1.0f, 1.0f, 10.0f);
            ImGui::End();

            camera.SetPosition(position);
            camera.SetFOV(fov);
            camera.SetNear(near);
            camera.SetFar(far);
            camera.SetPitch(pitch);
            camera.SetYaw(yaw);
            camera.SetSensitivity(sensitivity);
            camera.SetSpeed(speed);
        }

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
            camera.ProcessInput(static_cast<float>(window_w), static_cast<float>(window_h), dt);
        }

        camera.Update();

        shader.Use();

        shader.UploadFloat4x4("u_view", camera.GetView());
        shader.UploadFloat4x4("u_projection", camera.GetProjection(window_a));

        plane.Reset();
        plane.Scale(glm::vec3(8.0f, 8.0f, 8.0f));
        plane.Translate(glm::vec3(0.0f, 0.0f, 0.0f));
        plane.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        shader.UploadFloat4x4("u_model", plane.GetModel());

        plane.Draw();

        const float angle = static_cast<float>(glfwGetTime()) * glm::radians(-45.0f);

        for (const auto position: positions) {
            cube.Reset();
            cube.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
            cube.Translate(position);
            cube.Rotate(angle, glm::vec3(1.0f, 1.0f, 1.0f));

            shader.UploadFloat4x4("u_model", cube.GetModel());

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
}

Application &Application::GetInstance() {
    static Application instance;
    return instance;
}
