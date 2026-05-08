#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    float verticesL[] = {
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    float verticesU[] = {
        0.5f, 0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f  // top left
    };
    const int BUFFERS_COUNT = 2;
    const int ARRAYS_COUNT = 2;
    GLuint VBO[BUFFERS_COUNT];
    glGenBuffers(BUFFERS_COUNT, VBO);
    unsigned int VAO[ARRAYS_COUNT];
    glGenVertexArrays(ARRAYS_COUNT, VAO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesL), verticesL, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesL), verticesU, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSourceL = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "uniform vec4 ourColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                        // "FragColor = outColor;\n"
                                        "}\n";
    unsigned int fragmentShaderL;
    fragmentShaderL = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderL, 1, &fragmentShaderSourceL, NULL);
    glCompileShader(fragmentShaderL);

    const char *fragmentShaderSourceU = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "uniform vec4 ourColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        // "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                        "FragColor = ourColor;\n"
                                        "}\n";
    unsigned int fragmentShaderU;
    fragmentShaderU = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderU, 1, &fragmentShaderSourceU, NULL);
    glCompileShader(fragmentShaderU);

    unsigned int shaderProgramL;
    shaderProgramL = glCreateProgram();
    glAttachShader(shaderProgramL, vertexShader);
    glAttachShader(shaderProgramL, fragmentShaderL);
    glLinkProgram(shaderProgramL);
    unsigned int shaderProgramU;
    shaderProgramU = glCreateProgram();
    glAttachShader(shaderProgramU, vertexShader);
    glAttachShader(shaderProgramU, fragmentShaderU);
    glLinkProgram(shaderProgramU);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderL);
    glDeleteShader(fragmentShaderU);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.6f, 0.8f, 1.0f); // background
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramL);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramU);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramU, "ourColor");
        glUseProgram(shaderProgramU);
        glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
