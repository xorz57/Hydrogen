#include "Shader.hpp"
#include "Vertex.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    GLFWwindow *window = glfwCreateWindow(800, 600, "Example13", nullptr, nullptr);
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

    const std::vector<Vertex> vertices{
            {{-0.5f, -0.5f, -0.5f}, {+0.0f, +0.0f}},// 0
            {{+0.5f, -0.5f, -0.5f}, {+1.0f, +0.0f}},// 1
            {{+0.5f, +0.5f, -0.5f}, {+1.0f, +1.0f}},// 2
            {{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f}},// 3

            {{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f}},// 4
            {{+0.5f, -0.5f, +0.5f}, {+1.0f, +0.0f}},// 5
            {{+0.5f, +0.5f, +0.5f}, {+1.0f, +1.0f}},// 6
            {{-0.5f, +0.5f, +0.5f}, {+0.0f, +1.0f}},// 7

            {{-0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f}},// 8
            {{-0.5f, +0.5f, -0.5f}, {+1.0f, +1.0f}},// 9
            {{-0.5f, -0.5f, -0.5f}, {+0.0f, +1.0f}},// 10
            {{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f}},// 11

            {{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f}},// 12
            {{+0.5f, +0.5f, -0.5f}, {+1.0f, +1.0f}},// 13
            {{+0.5f, -0.5f, -0.5f}, {+0.0f, +1.0f}},// 14
            {{+0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f}},// 15

            {{-0.5f, -0.5f, -0.5f}, {+0.0f, +1.0f}},// 16
            {{+0.5f, -0.5f, -0.5f}, {+1.0f, +1.0f}},// 17
            {{+0.5f, -0.5f, +0.5f}, {+1.0f, +0.0f}},// 18
            {{-0.5f, -0.5f, +0.5f}, {+0.0f, +0.0f}},// 19

            {{-0.5f, +0.5f, -0.5f}, {+0.0f, +1.0f}},// 20
            {{+0.5f, +0.5f, -0.5f}, {+1.0f, +1.0f}},// 21
            {{+0.5f, +0.5f, +0.5f}, {+1.0f, +0.0f}},// 22
            {{-0.5f, +0.5f, +0.5f}, {+0.0f, +0.0f}},// 23
    };

    const std::vector<GLint> elements{
            0, 1, 2, 2, 3, 0,      // 0
            4, 5, 6, 6, 7, 4,      // 1
            8, 9, 10, 10, 11, 8,   // 2
            12, 13, 14, 14, 15, 12,// 3
            16, 17, 18, 18, 19, 16,// 4
            20, 21, 22, 22, 23, 20,// 5
    };

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));

    GLuint EBO = 0;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(GLfloat)), elements.data(), GL_STATIC_DRAW);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int texture_w, texture_h;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc *pixels = stbi_load("assets/textures/texture.png", &texture_w, &texture_h, nullptr, STBI_rgb_alpha);
    if (pixels) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_w, texture_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *) pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(pixels);
    }

    Shader shader = Shader::LoadFromFile("assets/shaders/shader_vert.glsl", "assets/shaders/shader_frag.glsl");

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///////////////////////////////////////////////////////////////////////

        shader.Use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(display_w) / static_cast<float>(display_h), 0.1f, 100.0f);

        shader.SetFloat4x4("u_Model", model);
        shader.SetFloat4x4("u_View", view);
        shader.SetFloat4x4("u_Projection", projection);

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

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();

    ///////////////////////////////////////////////////////////////////////////

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
