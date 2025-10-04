

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/Application.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    Application app(SCR_WIDTH,SCR_HEIGHT,"CoraGraphics");
    app.Run();
    return 0;
}



