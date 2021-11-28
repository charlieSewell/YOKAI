//
// Created by charl on 10/03/2021.
//
#include "Renderer/OpenGL/FileIO.hpp"

#include "stb_image.h"


unsigned char* TextureFromFile(const std::string& filename, int &width,int &height, int &nrComponents,int reqComponents)
{
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, reqComponents);
    return data;
}

void FreeTextureData(unsigned char* data)
{
    stbi_image_free(data);
}