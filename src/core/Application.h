#include <string>
#include "Window.h"

#include "../renderer/Mesh.h"
#include "../renderer/Shader.h"

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

    // Simple vertex and fragment shaders
    shader = new Shader("../src/shadertry.vs", "../src/shadertry.fs");

    // Define a square (two triangles)
    std::vector<float> vertices = {
        // positions         // normals       // texcoords
        0.5f,  0.5f, 0.0f,   0,0,1,          1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0,0,1,          1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0,0,1,          0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0,0,1,          0.0f, 1.0f  // top left
    };

    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    squareMesh = new Mesh(vertices, indices,"../src/container.jpg");

}

void Application::Run() {
    while (!window.ShouldClose()) {
        processInput(window.GetNativeWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the square

        squareMesh->Draw(*shader);
        
        window.SwapBuffers();
        window.PollEvents();
    }

    delete squareMesh;
    delete shader;
    glfwTerminate();
}

void processInput(GLFWwindow *window) { 
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true); 

}