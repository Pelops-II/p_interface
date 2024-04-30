#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

// Include GLAD, GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Include C++ standard libraries
#include <stdio.h>

// Include ImGui, ImPlot
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

// Include spdlog
#include "spdlog/spdlog.h"

#endif /* !INTERFACE_HPP_ */
