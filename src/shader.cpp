#include "shader.hpp"

Shader::Shader(const char* vert, const char* frag) {
    uint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vert, NULL);
    glCompileShader(vertShader);

    uint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &frag, NULL);
    glCompileShader(fragShader);
    
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}