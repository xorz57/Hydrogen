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

    Shader shader = Shader::LoadFromFile("assets/shaders/default_vert.glsl", "assets/shaders/default_frag.glsl");
    Shader light_shader = Shader::LoadFromFile("assets/shaders/light_vert.glsl", "assets/shaders/light_frag.glsl");

    Material emerald{glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 128.0f};
    Material jade{glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f * 128.0f};
    Material obsidian{glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f * 128.0f};
    Material pearl{glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f * 128.0f};
    Material ruby{glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f * 128.0f};
    Material turquoise{glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f * 128.0f};
    Material brass{glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f * 128.0f};
    Material bronze{glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f), 0.2f * 128.0f};
    Material chrome{glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f * 128.0f};
    Material copper{glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f * 128.0f};
    Material gold{glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f * 128.0f};
    Material silver{glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f), 0.4f * 128.0f};

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

        shader.Use();

        shader.SetFloat4x4("u_view", camera.GetView());
        shader.SetFloat4x4("u_projection", camera.GetProjection(window_a));

        Light light;
        light.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
        light.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        const glm::vec3 light_position(32.0f + 64.0f * sin(glfwGetTime()), 64.0f, 32.0f + 64.0f * cos(glfwGetTime()));

        shader.SetFloat3("u_light.ambient", light.ambient);
        shader.SetFloat3("u_light.diffuse", light.diffuse);
        shader.SetFloat3("u_light.specular", light.specular);
        shader.SetFloat3("u_camera_position", camera.GetPosition());
        shader.SetFloat3("u_light_position", light_position);

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", emerald.ambient);
            shader.SetFloat3("u_material.diffuse", emerald.diffuse);
            shader.SetFloat3("u_material.specular", emerald.specular);
            shader.SetFloat("u_material.shininess", emerald.shininess);
            shader.SetFloat4x4("u_model", model);
            triangle.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", copper.ambient);
            shader.SetFloat3("u_material.diffuse", copper.diffuse);
            shader.SetFloat3("u_material.specular", copper.specular);
            shader.SetFloat("u_material.shininess", copper.shininess);
            shader.SetFloat4x4("u_model", model);
            quad.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(64.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", chrome.ambient);
            shader.SetFloat3("u_material.diffuse", chrome.diffuse);
            shader.SetFloat3("u_material.specular", chrome.specular);
            shader.SetFloat("u_material.shininess", chrome.shininess);
            shader.SetFloat4x4("u_model", model);
            cube.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", brass.ambient);
            shader.SetFloat3("u_material.diffuse", brass.diffuse);
            shader.SetFloat3("u_material.specular", brass.specular);
            shader.SetFloat("u_material.shininess", brass.shininess);
            shader.SetFloat4x4("u_model", model);
            plane.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", gold.ambient);
            shader.SetFloat3("u_material.diffuse", gold.diffuse);
            shader.SetFloat3("u_material.specular", gold.specular);
            shader.SetFloat("u_material.shininess", gold.shininess);
            shader.SetFloat4x4("u_model", model);
            circle.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(64.0f, 0.0f, 32.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", jade.ambient);
            shader.SetFloat3("u_material.diffuse", jade.diffuse);
            shader.SetFloat3("u_material.specular", jade.specular);
            shader.SetFloat("u_material.shininess", jade.shininess);
            shader.SetFloat4x4("u_model", model);
            sphere.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 64.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", obsidian.ambient);
            shader.SetFloat3("u_material.diffuse", obsidian.diffuse);
            shader.SetFloat3("u_material.specular", obsidian.specular);
            shader.SetFloat("u_material.shininess", obsidian.shininess);
            shader.SetFloat4x4("u_model", model);
            cylinder.Draw();
        }

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(32.0f, 0.0f, 64.0f));
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            shader.SetFloat3("u_material.ambient", pearl.ambient);
            shader.SetFloat3("u_material.diffuse", pearl.diffuse);
            shader.SetFloat3("u_material.specular", pearl.specular);
            shader.SetFloat("u_material.shininess", pearl.shininess);
            shader.SetFloat4x4("u_model", model);
            capsule.Draw();
        }

        light_shader.Use();

        light_shader.SetFloat4x4("u_view", camera.GetView());
        light_shader.SetFloat4x4("u_projection", camera.GetProjection(window_a));

        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, light_position);
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(16.0f, 16.0f, 16.0f));

            light_shader.SetFloat4x4("u_model", model);
            light_sphere.Draw();
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
