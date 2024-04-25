#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cinttypes>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
    if (!glfwInit()) {
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Example4", nullptr, nullptr);
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

    std::clog << "OpenGL Vendor: " << (const char *) glGetString(GL_VENDOR) << std::endl;
    std::clog << "OpenGL Renderer: " << (const char *) glGetString(GL_RENDERER) << std::endl;
    std::clog << "OpenGL Version: " << (const char *) glGetString(GL_VERSION) << std::endl;
    std::clog << "OpenGL Shading Language Version: " << (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

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

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    const std::vector<GLfloat> vertices1{
            +0.5f, -0.5f, +0.0f,
            -0.5f, -0.5f, +0.0f,
            +0.0f, +0.5f, +0.0f};

    GLuint VBO1 = 0;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices1.size() * sizeof(GLfloat)), vertices1.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) nullptr);

    const std::vector<GLfloat> vertices2{
            +1.0f, +0.0f, +0.0f,
            +0.0f, +1.0f, +0.0f,
            +0.0f, +0.0f, +1.0f};

    GLuint VBO2 = 0;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices2.size() * sizeof(GLfloat)), vertices2.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) nullptr);

    const std::vector<GLint> elements{0, 1, 2};

    GLuint EBO = 0;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(GLfloat)), elements.data(), GL_STATIC_DRAW);

    const char *vShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 v_Color;

void main() {
    gl_Position = vec4(position, 1.0);
    v_Color = color;
}
        )";

    const char *fShaderSource = R"(
#version 330 core

out vec4 f_Color;
in vec3 v_Color;

void main() {
    f_Color = vec4(v_Color, 1.0);
}
        )";

    GLint success;

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, nullptr);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vShader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, nullptr);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fShader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    GLint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
        std::cerr << infoLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glDetachShader(program, vShader);
    glDetachShader(program, fShader);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

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

        ImGui::Render();

        int display_w;
        int display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ///////////////////////////////////////////////////////////////////////

        glUseProgram(program);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(elements.size()), GL_UNSIGNED_INT, (void *) nullptr);

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

    glDeleteProgram(program);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO);

    ///////////////////////////////////////////////////////////////////////////

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}