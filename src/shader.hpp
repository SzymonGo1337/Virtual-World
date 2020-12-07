#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

using Mat4 = glm::mat4x4;
using uint = uint32_t;

class Shader {
public:
    Shader(const char* vert, const char* frag);

    void Bind() { glUseProgram(program); }
    void Unbind() { glUseProgram(0); }

    uint GetProgram() { return program; }

private:
    uint program;
};