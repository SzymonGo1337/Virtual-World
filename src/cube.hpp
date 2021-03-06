#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL2/stb_image.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "shader.hpp"
#include "texture.hpp"

#define WIDTH 1280
#define HEIGHT 720

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

class Cube {
public:
    Cube();
    Cube(float x, float y, float z);

    void BindVBO() { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
    void BindVAO() { glBindVertexArray(VAO); }
    void BindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); }

    unsigned int GetVBO() { return VBO; }
    unsigned int GetVAO() { return VAO; }
    unsigned int GetIBO() { return IBO; }

    glm::vec3 GetPos() { return pos; }

    void UnbindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    void UnbindVAO() { glBindVertexArray(0); }
    void UnbindIBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    void render(uint transform);

private:
    glm::vec3 pos;
    Mat4 cubeTransform;
    unsigned int VBO, VAO, IBO;
};