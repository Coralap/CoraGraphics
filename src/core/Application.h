#include <string>
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../camera/camera.h"
#include "../renderer/Mesh.h"
#include "../renderer/Shader.h"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
void processInput(GLFWwindow *window);
class Application {
public:
    unsigned int width;
    unsigned int height;
    std::string name;
    Window window;

    Shader* shader;
    Mesh* squareMesh;
    Texture* texture;

    Camera* camera;
    Application(unsigned int width, unsigned int height, const std::string name);
    void Run();
};

Application::Application(unsigned int width, unsigned int height, const std::string name)
    : width(width), height(height), name(name), window(width, height, name)
{   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }    
    camera = new Camera(glm::vec3(0.0f,0.0f,3.0f));
    // Simple vertex and fragment shaders
    shader = new Shader("../src/shadertry.vs", "../src/shadertry.fs");

    // Define a square (two triangles)
std::vector<float> vertices = {
    // positions           // normals          // texcoords
    // Front face
   -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,

    // Back face
   -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,

    // Left face
   -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

    // Right face
    0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

    // Top face
   -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

    // Bottom face
   -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
};


std::vector<unsigned int> indices = {
    // front
    0, 1, 2, 0, 2, 3,
    // back
    4, 5, 6, 4, 6, 7,
    // left
    8, 9,10, 8,10,11,
    // right
   12,13,14,12,14,15,
    // top
   16,17,18,16,18,19,
    // bottom
   20,21,22,20,22,23
};


    squareMesh = new Mesh(vertices, indices,"../src/container.jpg");


}

void Application::Run() {
    // -----------------------------
    // Setup ImGui context
    // -----------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.0+ compatible

    // Color variable controlled by GUI
    float clear_color[3] = {0.2f, 0.3f, 0.3f};
    float position[3] = {0,0,0};
    float rotation[3] = {0,0,0};
    float scale[3] = {1,1,1};
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    // Main loop
    while (!window.ShouldClose()) {
        processInput(window.GetNativeWindow());

        // -----------------------------
        // Start ImGui frame
        // -----------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // -----------------------------
        // Example GUI
        // -----------------------------

        ImGui::Begin("Transform");
        ImGui::Text("Change Object Transform");
        ImGui::DragFloat3("Set position", position,0.05f);
        ImGui::DragFloat3("Set roation", rotation,0.05f);
        ImGui::DragFloat3("Set scale", scale,0.05f,0.0f);
        ImGui::End();

        // -----------------------------
        // Render scene
        // -----------------------------
        glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        squareMesh->transform.position = glm::vec3(position[0],position[1],position[2]);
        squareMesh->transform.rotation = glm::vec3(rotation[0],rotation[1],rotation[2]);
        squareMesh->transform.scale = glm::vec3(scale[0],scale[1],scale[2]);


        shader->setMat4("model",squareMesh->transform.getModelMatrix());
        shader->setMat4("projection",projection);
        shader->setMat4("view", camera->GetViewMatrix());
        squareMesh->Draw(*shader);

        // -----------------------------
        // Render ImGui
        // -----------------------------
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
        window.PollEvents();
    }

    // -----------------------------
    // Cleanup
    // -----------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete squareMesh;
    delete shader;
    glfwTerminate();
}

void processInput(GLFWwindow *window) { 
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true); 

}