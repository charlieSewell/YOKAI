#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bgfx/embedded_shader.h>
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif // BX_PLATFORM_

#include <bx/math.h>
#include <bx/timer.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "bgfxutil.hpp"
#include <GLFW/glfw3native.h>
#include <spdlog/spdlog.h>

void ImGui_Implbgfx_Init(int view);
void ImGui_Implbgfx_Shutdown();
void ImGui_Implbgfx_NewFrame();
void ImGui_Implbgfx_RenderDrawLists(struct ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
void ImGui_Implbgfx_InvalidateDeviceObjects();
bool ImGui_Implbgfx_CreateDeviceObjects();
