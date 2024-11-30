#include "Application.hpp"

#include "Camera.hpp"
#include "Logging.hpp"
#include "Shader.hpp"

#include "Shapes/Capsule.hpp"
#include "Shapes/Circle.hpp"
#include "Shapes/Cube.hpp"
#include "Shapes/Cylinder.hpp"
#include "Shapes/Plane.hpp"
#include "Shapes/Quad.hpp"
#include "Shapes/Sphere.hpp"
#include "Shapes/Triangle.hpp"

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

static void glfw_error_callback(const int error, const char *description) {
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void Application::Run() {
    Logging::Init();

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Example16", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    SERVER_INFO("OpenGL Vendor: {}", reinterpret_cast<const GLchar *>(glGetString(GL_VENDOR)));
    SERVER_INFO("OpenGL Renderer: {}", reinterpret_cast<const GLchar *>(glGetString(GL_RENDERER)));
    SERVER_INFO("OpenGL Version: {}", reinterpret_cast<const GLchar *>(glGetString(GL_VERSION)));
    SERVER_INFO("OpenGL Shading Language Version: {}", reinterpret_cast<const GLchar *>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

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

    Camera camera;
    camera.SetPosition(glm::vec3(+0.0f, +16.0f, +16.0f));
    camera.SetFOV(90.0f);
    camera.SetNear(0.1f);
    camera.SetFar(256.0f);
    camera.SetPitch(45.0f);
    camera.SetYaw(-90.0f);
    camera.SetSensitivity(0.1f);
    camera.SetSpeed(4.0f);

    Capsule capsule;
    Circle circle;
    Cube cube;
    Cylinder cylinder;
    Plane plane;
    Quad quad;
    Sphere sphere;
    Triangle triangle;

    Shader shader = Shader::LoadFromFile("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");

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
        if (ImGui::BeginTable("##statistics_table", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableNextColumn();
            ImGui::Text("Frame");
            ImGui::TableNextColumn();
            ImGui::Text("%" PRIu64, frame);

            ImGui::TableNextColumn();
            ImGui::Text("Delta Time");
            ImGui::TableNextColumn();
            ImGui::Text("%.8lf sec", dt);

            ImGui::EndTable();
        }
        ImGui::End();

        ImGui::Begin("Settings");
        ImGui::Checkbox("Wireframe", &mWireframe);
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

        if (mWireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        camera.ProcessInput(static_cast<float>(window_w), static_cast<float>(window_h), dt);

        camera.Update();

        shader.Use();

        shader.SetFloat4x4("u_view", camera.GetView());
        shader.SetFloat4x4("u_projection", camera.GetProjection(window_a));

        triangle.Reset();
        triangle.Translate(glm::vec3(0.0f, 0.0f, 0.0f));
        triangle.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        triangle.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", triangle.GetModel());
        triangle.Draw();

        quad.Reset();
        quad.Translate(glm::vec3(32.0f, 0.0f, 0.0f));
        quad.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        quad.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", quad.GetModel());
        quad.Draw();

        cube.Reset();
        cube.Translate(glm::vec3(64.0f, 0.0f, 0.0f));
        cube.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        cube.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", cube.GetModel());
        cube.Draw();

        plane.Reset();
        plane.Translate(glm::vec3(0.0f, 0.0f, 32.0f));
        plane.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        plane.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", plane.GetModel());
        plane.Draw();

        circle.Reset();
        circle.Translate(glm::vec3(32.0f, 0.0f, 32.0f));
        circle.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        circle.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", circle.GetModel());
        circle.Draw();

        sphere.Reset();
        sphere.Translate(glm::vec3(64.0f, 0.0f, 32.0f));
        sphere.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        sphere.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", sphere.GetModel());
        sphere.Draw();

        cylinder.Reset();
        cylinder.Translate(glm::vec3(0.0f, 0.0f, 64.0f));
        cylinder.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        cylinder.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", cylinder.GetModel());
        cylinder.Draw();

        capsule.Reset();
        capsule.Translate(glm::vec3(32.0f, 0.0f, 64.0f));
        capsule.Rotate(glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        capsule.Scale(glm::vec3(16.0f, 16.0f, 16.0f));
        shader.SetFloat4x4("u_model", capsule.GetModel());
        capsule.Draw();

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

    capsule.Delete();
    circle.Delete();
    cube.Delete();
    cylinder.Delete();
    plane.Delete();
    quad.Delete();
    sphere.Delete();
    triangle.Delete();

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
