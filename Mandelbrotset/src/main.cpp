#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

const int width =   800;
const int height =  600;
const float minReal = -2.0f;
const float maxReal = 1.0f;
const float minImg = -1.5f;
const float maxImg = 1.5f;

const int maxIterations = 1000;
const int threshold = 2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int mandelbrotCalculation(float x, float y)
{
    float cReal = minReal + (x/width) * (maxReal - minReal);
    float cImg = maxImg + (y/height) * (maxImg - minImg);
    float zReal = 0f;
    float zImg = 0f;

    for (int iterations = 0; iterations < maxIterations; iterations++)
    {
        float zRealNew = zReal * zReal - zImg * zImg + cReal;
        float zImgNew = 2 * zReal * zImg + cImg;
        zReal = zRealNew;
        zImg = zImgNew;
        if (zReal * zReal + zImg * zImg > threshold)
        {
            break;
        }
        return maxIterations;
    }
}


int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "FÖNSTER", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if  (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        // Input.
        processInput(window);

        // Rendering commands here:


        // Check and call events and swap the buffers.
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    glfwTerminate();
    return 0;
}