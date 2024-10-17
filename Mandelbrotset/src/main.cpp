#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int width = 720;
const int height = 720;
double minReal = -2.0;
double maxReal = 1.0;
double minImg = -1.5;
double maxImg = 1.5;
double maxIterations = 10.0;
double zoom = 1.0;

// Vertex shader source
const char* vertexSource = R"(
    #version 460 compatibility
    layout (location = 0) in vec2 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

// Fragment shader source
const char* fragmentSource = R"(
    #version 460 core
    out vec4 FragColor;

    uniform double minReal;
    uniform double maxReal;
    uniform double minImg;
    uniform double maxImg;
    uniform int maxIterations;

    const vec3 color_map[4] = vec3[](
        vec3(0.19, 0.01, 0.20),   // Magenta
        vec3(0.5, 0.0, 0.5),      // Purple
        vec3(1.0, 0.6, 0.4),      // Cantaloupe orange
        vec3(0.0, 0.0, 0.5)       // Dark blue
    );

    void main()
    {
        double x = double(gl_FragCoord.x);
        double y = double(gl_FragCoord.y);

        double cReal = minReal + (x / 720.0) * (maxReal - minReal);
        double cImg = maxImg - (y / 720.0) * (maxImg - minImg);

        double zReal = 0.0;
        double zImg = 0.0;
        int iterations;
        for (iterations = 0; iterations < maxIterations; iterations++) {
            double zRealNew = zReal * zReal - zImg * zImg + cReal;
            double zImgNew = 2.0 * zReal * zImg + cImg;
            zReal = zRealNew;
            zImg = zImgNew;
            if (zReal * zReal + zImg * zImg > 4.0) break;
        }

        if (iterations == maxIterations) {
            FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black color for Mandelbrot set
        } else {
            float t = float(iterations) / float(maxIterations);
            float mappedIndex = t * (float(color_map.length()) - 1.0);
            int index1 = int(floor(mappedIndex));
            int index2 = min(index1 + 1, color_map.length() - 1);
            float mixFactor = fract(mappedIndex);
            vec3 color = mix(color_map[index1], color_map[index2], mixFactor);

            FragColor = vec4(color, 1.0);
        }
    }
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Mandelbrot Viewer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f,  1.0f,
        -1.0f, -1.0f, 1.0f,  1.0f, -1.0f,  1.0f
    };
    
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    GLuint shaderProgram = createShaderProgram(vertexSource, fragmentSource);
    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Zoom in
        zoom *= 1.1;
        maxIterations *= 1.1;

        // Update complex plane bounds
        double currentMinReal = -2.0 / zoom;
        double currentMaxReal = 1.0 / zoom;
        double currentMinImg = -1.5 / zoom;
        double currentMaxImg = 1.5 / zoom;

        // Send uniforms to shader
        glUniform1d(glGetUniformLocation(shaderProgram, "minReal"), currentMinReal);
        glUniform1d(glGetUniformLocation(shaderProgram, "maxReal"), currentMaxReal);
        glUniform1d(glGetUniformLocation(shaderProgram, "minImg"), currentMinImg);
        glUniform1d(glGetUniformLocation(shaderProgram, "maxImg"), currentMaxImg);
        glUniform1i(glGetUniformLocation(shaderProgram, "maxIterations"), int(maxIterations));

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
