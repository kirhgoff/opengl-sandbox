// Local Headers
#include "glitter.hpp"

// System Headers

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <shader.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLchar* vertexShaderSource = " \
    #version 410 core \
    layout (location = 0) in vec3 position; \
    layout (location = 1) in vec3 color;\
    out vec3 ourColor;\
    void main() { \
        gl_Position = vec4(position, 1.0);\
        ourColor = color;\
    }";

const GLchar* fragmentShaderSource = " \
    #version 410 core \
    uniform float multiplier;\
    in vec3 ourColor;\
    out vec4 color; \
    void main() { \
        color = vec4(ourColor.x * (1 -  multiplier), ourColor.y * multiplier, ourColor.z, 1.0f); \
    }";

int main(int argc, char * argv[]) {
    
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    auto window = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);
    glfwSetKeyCallback(window, key_callback);

    // Check for Valid Context
    if (window == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    fprintf(stderr, "Maximum nr of vertex attributes supported: %d\n", nrAttributes);

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //=========================================================
    // Init objects
    //=========================================================

    GLfloat vertices[] = {
            // Positions         // Colors
            0.5f,   -0.5f,   0.0f,  1.0f, 0.0f, 0.0f,  // Bottom Right
            -0.5f,  -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
            0.0f,   0.5f,  0.0f,  0.0f, 0.0f, 1.0f   // Top
    };

    GLfloat texCoords[] = {
            0.0f, 0.0f, // Lower-left corner
            1.0f, 0.0f, // Lower-right corner
            0.5f, 1.0f // Top-center corner
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Shader ourShader(
        "/Users/klastovirya/Projects/Glitter/Glitter/Shaders/shader.vert",
        "/Users/klastovirya/Projects/Glitter/Glitter/Shaders/shader.frag"
    );

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();

        GLfloat timeValue = glfwGetTime();
        GLfloat multiplierValue = (sin(timeValue) / 2) + 0.5;
        GLint multiplierLocation = glGetUniformLocation(ourShader.Program, "multiplier");
        glUniform1f(multiplierLocation, multiplierValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Flip Buffers and Draw
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return EXIT_SUCCESS;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
