#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

const int width = 1280;
const int height = 720;

const int threshold = 2;

const double minReal = -2.0;
const double maxReal = 1.0;
const double minImg = -1.5;
const double maxImg = 1.5;

double maxIterations = 200;

const char* fragmentSource = R"(
#version 420 core
out vec4 FragColor;

uniform double minReal;
uniform double maxReal;
uniform double minImg;
uniform double maxImg;
uniform double maxIterations;

// Definierar färg karta.
const vec3 color-map[5] = vec3[]
(
    vec3(0, 1, 0),      // Lime grön.
    vec3(1, 1, 0),      // Citron gul.
    vec3(1, 0, 0),      // Röd röd.
    vec3(0, 0, 1)       // Blå blå.
    vec3(1, 1, 1)       // Krit-vit.
);

void main()
{
    //Skärm koordinater.
    double x = gl_FragCoord.x;
    double y = gl_FragCoord.y;

    // Kartlägger skärmens koordinater till de komplexa talens verklighet.
    double cReal = minReal + (x / 1280.0) * (maxReal - minReal);
    double cImg = maxImg - (y / 720.0) * (maxImg - minImg);

    // Mandelbrot uträkningen.
    double zReal = 0.0;
    double zImg = 0.0;
    double iterations;

    for (iterations = 0; iterations < maxIterations; iterations ++)
    {
        double zRealNew = zReal * zReal - zImg * zImg + cReal;
        double zImgNew = 2.0 * zReal * zImg + cImg;
        zReal = zRealNew;
        zImg = zImgNew;

        if (zReal * zReal + zImg * zImg > 4.0) break;
    }

    // Om punkten som beräknas är innanför Mandelbrotmängden, ska den bli svart.
    if (iterations == maxIterations)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Den svarta färgen.
    }
    else
    {
        // Beräknar normaliserade iterationers värde för punkterna utanför Mandelbrotmängden.
        double t = iterations / maxIterations;

        // 
        double mappedIndex = t * (double(color_map.length()) - 1.0);
        int index1 = int(floor(mappedIndex));
        int index2 = min(index1 + 1, color_map.length() - 1)

        // Interpolera mellan de två färgerna i färg kartan.
        double mixFactor = fract(mappedIndex); // Fraktala delen av indexen.
        vec3 color = mix(color_map[index1], color_map[index2], mixFactor);
        
        FragColor = vec4(color, 1.0):
    }

}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldCLose(window, true);
    }
}

int mandelbrotCalculation(int x, int y)
{
    // Konverterar pixelkoordinater till komplexa koordinater.
    double cReal = minReal + (static_cast<double>(x) / width) * (maxReal - minReal);
    double cImg = maxImg - (static_cast<double>(y) / height) * (maxImg - minImg);


}