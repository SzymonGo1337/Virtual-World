#include "core.hpp"

Vertex verts[] = {
    //front
    {{-0.5f, -0.5f, 0.5f},  {0.0f, 1.0f}},
    {{0.5f, -0.5f, 0.5f},   {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f},   {0.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f},    {1.0f, 0.0f}},

    //right
    {{0.5f, -0.5f, 0.5f},   {0.0f, 1.0f}},
    {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f},    {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f},   {1.0f, 0.0f}},

    //back
    {{0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f},   {0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f}},

    //left
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f},  {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f},  {0.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f},   {1.0f, 0.0f}},

    //top
    {{-0.5f, 0.5f, 0.5f},   {0.0f, 1.0f}},
    {{0.5f, 0.5f, 0.5f},    {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f},  {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f},   {1.0f, 0.0f}},

    //bottom
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f},   {1.0f, 0.0f}},
};

uint indices[] = {
    0, 2, 1, 1, 2, 3, //front
    4, 6, 5, 5, 6, 7, //right
    8, 10, 9, 9, 10, 11, //back
    12, 14, 13, 13, 14, 15, //left
    16, 18, 17, 17, 18, 19, //top
    20, 22, 21, 21, 22, 23 //bottom 
};

Cube::Cube() {
    cubeTransform = glm::translate(Mat4(1), glm::vec3(0, -1, -3));

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));

    //Index Buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Cube::Cube(float x, float y, float z) {
    cubeTransform = glm::translate(Mat4(1), glm::vec3(x, y, z));

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));

    //Index Buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Cube::render(uint transform) {
    BindVAO();
    glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(cubeTransform));
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint), GL_UNSIGNED_INT, 0);
    UnbindVAO();
}