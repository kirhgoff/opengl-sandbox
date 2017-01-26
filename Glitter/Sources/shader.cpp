//
// Created by Kirill Lastovirya on 26/1/17.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include "shader.hpp"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

    const GLchar *vertexShaderCode = readShaderFile(vertexPath);
    const GLchar *fragmentShaderCode = readShaderFile(fragmentPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertexShader);
    glAttachShader(this->Program, fragmentShader);
    glLinkProgram(this->Program);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::compileShader(int shaderType, const GLchar *&code) const {
    GLint success;
    GLchar infoLog[512];

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
    };
    return shader;
}

GLchar *Shader::readShaderFile(const GLchar *path) const {
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path);
        stringstream vShaderStream;
        vShaderStream << file.rdbuf();
        file.close();
        code = vShaderStream.str();
    } catch (ios_base::failure e) {
        fprintf(stderr, "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: %s", path);
    }

    return (GLchar *)code.c_str();
}

void Shader::Use() { glUseProgram(this->Program); }