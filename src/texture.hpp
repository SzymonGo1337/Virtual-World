#pragma once
#include <glad/glad.h>
#include <iostream>
#include <SOIL2/stb_image.h>

#include "core.hpp"

class Texture {
public:
    Texture(const char* filename);

    void Bind() { glBindTexture(GL_TEXTURE_2D, texture); }
    void Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

private:
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char *data;
};