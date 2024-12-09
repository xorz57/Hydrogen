#include "Application.hpp"

#include "Camera.hpp"
#include "Light.hpp"
#include "Logging.hpp"
#include "Material.hpp"
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

    Sphere light_sphere;

    Shader light_shader = Shader::LoadFromFile("assets/shaders/light_vert.glsl", "assets/shaders/light_frag.glsl");
    Shader shader = Shader::LoadFromFile("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");

    Light light;
    light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

    Material material;
    material.ambient = glm::vec3(0.5f, 0.25f, 0.75f);
    material.diffuse = glm::vec3(0.5f, 0.25f, 0.75f);
    material.specular = glm::vec3(0.25f, 0.25f, 0.25f);
    material.shininess = 32.0f;

    ///////////////////////////////////////////////////////////////////////////

    std::uint64_t frame = 0;
    double t0 = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        ++frame;
        const double t1 = glfwGetTime();
        const double dt = t1 - t0;
        t0 = t1;

        glfwPollEvents();

        int window_w;
        int window_h;
        glfwGetFramebufferSize(window, &window_w, &window_h);
        glViewport(0, 0, window_w, window_h);

        const float window_a = static_cast<float>(window_w) / static_cast<float>(window_h);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        ///////////////////////////////////////////////////////////////////////

        static bool wireframe = false;

        ImGui::Begin("Settings");
        ImGui::Checkbox("Wireframe", &wireframe);
        ImGui::End();

        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        camera.ProcessInput(static_cast<float>(window_w), static_cast<float>(window_h), dt);

        camera.Update();

        ImGui::Begin("Light");
        ImGui::DragFloat3("Ambient", (float *) &light.ambient, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Diffuse", (float *) &light.diffuse, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Specular", (float *) &light.specular, 0.01f, 0.0f, 1.0f);
        ImGui::End();

        light.position = glm::vec3(32.0f + 64.0f * sin(glfwGetTime()), 64.0f, 32.0f + 64.0f * cos(glfwGetTime()));

        light_shader.Use();

        light_shader.SetMat4("u_view", camera.GetView());
        light_shader.SetMat4("u_projection", camera.GetProjection(window_a));

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, light.position);
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            light_shader.SetMat4("u_model", model);

            light_sphere.Draw();
        }

        shader.Use();

        shader.SetMat4("u_view", camera.GetView());
        shader.SetMat4("u_projection", camera.GetProjection(window_a));

        shader.SetVec3("u_light.position", light.position);
        shader.SetVec3("u_light.ambient", light.ambient);
        shader.SetVec3("u_light.diffuse", light.diffuse);
        shader.SetVec3("u_light.specular", light.specular);

        shader.SetVec3("u_camera_position", camera.GetPosition());

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            triangle.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            quad.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(64.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            cube.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            plane.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            circle.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(64.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            sphere.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 64.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            cylinder.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 64.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetVec3("u_material.ambient", material.ambient);
            shader.SetVec3("u_material.diffuse", material.diffuse);
            shader.SetVec3("u_material.specular", material.specular);
            shader.SetFloat("u_material.shininess", material.shininess);

            shader.SetMat4("u_model", model);

            capsule.Draw();
        }

        ///////////////////////////////////////////////////////////////////////

        ImGui::Render();

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

    light_shader.Delete();
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
