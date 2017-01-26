//
// Created by Kirill Lastovirya on 26/1/17.
//

#ifndef GLITTER_SHADER_HPP
#define GLITTER_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
    GLuint Program;
    Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
    void Use();

};


#endif //GLITTER_SHADER_HPP
