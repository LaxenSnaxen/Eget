#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>

const int width =   1920;
const int height =  1080;
const float minReal = -2.0f;
const float maxReal = 1.0f;
const float minImg = -1.5f;
const float maxImg = 1.5f;

double maxIterations = 100;
const int threshold = 2;
const char* vertexSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";
const char* fragmentSource = R"(
#version 420 core
out vec4 FragColor;

uniform float minReal;
uniform float maxReal;
uniform float minImg;
uniform float maxImg;
uniform int maxIterations;

// Define a color map with magenta, purple, cantaloupe orange, and dark blue
const vec3 color_map[4] = vec3[](
    vec3(0.19, 0.01, 0.20),   // Magenta
    vec3(0.5, 0.0, 0.5),   // Purple
    vec3(1.0, 0.6, 0.4),   // Cantaloupe orange
    vec3(0.0, 0.0, 0.5)    // Dark blue
);

void main()
{
    // Screen coordinates
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;

    // Map screen coordinates to complex plane
    float cReal = minReal + (x / 1920.0) * (maxReal - minReal);
    float cImg = maxImg - (y / 1080.0) * (maxImg - minImg);

    // Mandelbrot calculation
    float zReal = 0.0;
    float zImg = 0.0;
    int iterations;
    for (iterations = 0; iterations < maxIterations; iterations++) {
        float zRealNew = zReal * zReal - zImg * zImg + cReal;
        float zImgNew = 2.0 * zReal * zImg + cImg;
        zReal = zRealNew;
        zImg = zImgNew;
        if (zReal * zReal + zImg * zImg > 4.0) break;
    }

    // If point is in the Mandelbrot set, make it black
    if (iterations == maxIterations) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black color for Mandelbrot set
    } else {
        // Calculate normalized iteration value for points outside Mandelbrot set
        float t = float(iterations) / float(maxIterations);

        // Map `t` to color_map index range [0, 3]
        float mappedIndex = t * (float(color_map.length()) - 1.0);
        int index1 = int(floor(mappedIndex));
        int index2 = min(index1 + 1, color_map.length() - 1);  // Avoid going out of bounds

        // Interpolate between the two colors in the map
        float mixFactor = fract(mappedIndex);  // Fractional part of the index
        vec3 color = mix(color_map[index1], color_map[index2], mixFactor);

        FragColor = vec4(color, 1.0);
    }
}
)";


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

int mandelbrotCalculation(int x, int y)
{
    // Konvertera pixelkoordinater till komplexa koordinater
    float cReal = minReal + (static_cast<float>(x) / width) * (maxReal - minReal);
    float cImg = maxImg - (static_cast<float>(y) / height) * (maxImg - minImg);

    // Initiera z till (0, 0)
    float zReal = 0.0f;
    float zImg = 0.0f;

    // Mandelbrot-iterationerna
    for (int iterations = 0; iterations < maxIterations; iterations++)
    {
        // Beräkna z^2 + c
        float zRealNew = zReal * zReal - zImg * zImg + cReal;
        float zImgNew = 2 * zReal * zImg + cImg;

        zReal = zRealNew;
        zImg = zImgNew;

        // Kontrollera om vi har flykt
        if (zReal * zReal + zImg * zImg > threshold)
        {
            return iterations;  // Returnera antalet iterationer tills vi flydde
        }
    }

    // Returnera maxIterations om punkten tillhör Mandelbrot-mängden
    return maxIterations;
}

GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource)
{
    // Skapa och kompilera vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Kontrollera om vertex shader kompilerades korrekt
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Skapa och kompilera fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Kontrollera om fragment shader kompilerades korrekt
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Skapa shaderprogram och länka shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Kontrollera om länkningen gick bra
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Rensa upp, ta bort shaders eftersom de är länkade till programmet
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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
    // Vertices för en fyrkant som täcker hela skärmen
    float vertices[] = {
        // x, y
        -1.0f, -1.0f, // Vänster nedre hörn
         1.0f, -1.0f, // Höger nedre hörn
         1.0f,  1.0f, // Höger övre hörn
        -1.0f, -1.0f, // Vänster nedre hörn
         1.0f,  1.0f, // Höger övre hörn
        -1.0f,  1.0f  // Vänster övre hörn
    };
    
    // Skapa VAO och VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Binda VAO
    glBindVertexArray(VAO);
    
    // Binda och ladda VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Specificera attributen för vertexshadern (layout(location = 0) in vec2 aPos)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Unbind VBO och VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    GLuint shaderProgram = createShaderProgram(vertexSource, fragmentSource);
    glUseProgram(shaderProgram);

    double zoom = 1.0;

    // Intressant koordinat för att se detaljer i Mandelbrot-mängden
    float centerRe = -0.74364388703f;
    float centerIm = 0.13182590421f;
    int counter = 0;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // Zooma in långsamt
        zoom *= 0.99;
        maxIterations *= 1.005;
        //std::cout << zoom << std::endl;
        // Beräkna de nya gränserna för det komplexa planet baserat på zoom och centrum
        float minReal = centerRe - (1.5f * zoom);
        float maxReal = centerRe + (1.5f * zoom);
        float minImg = centerIm - (1.0f * zoom);
        float maxImg = centerIm + (1.0f * zoom);
        

        // Skicka de nya gränserna till shadern
        glUniform1f(glGetUniformLocation(shaderProgram, "minReal"), minReal);
        glUniform1f(glGetUniformLocation(shaderProgram, "maxReal"), maxReal);
        glUniform1f(glGetUniformLocation(shaderProgram, "minImg"), minImg);
        glUniform1f(glGetUniformLocation(shaderProgram, "maxImg"), maxImg);
        glUniform1i(glGetUniformLocation(shaderProgram, "maxIterations"), maxIterations);

        // Rensa skärmen och rendera
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);  // Ritar två trianglar som täcker hela skärmen
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





        glfwTerminate();
        return 0;
    }