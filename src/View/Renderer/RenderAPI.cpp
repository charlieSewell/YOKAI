//
// Created by Charlie Sewell on 10/03/2021.
//
#include "View/Renderer/OpenGL/OpenGLRenderer.hpp"

std::shared_ptr<RenderAPI> RenderAPI::Create()
{
    return std::shared_ptr<RenderAPI>(new OpenGLRenderer());
}