//
// Created by Charlie Sewell on 10/03/2021.
//
#include "bgfx/bgfxRenderer.hpp"

std::shared_ptr<RenderAPI> RenderAPI::Create(GLFWwindow* window)
{
    return std::shared_ptr<RenderAPI>(new bgfxRenderer(window));
}